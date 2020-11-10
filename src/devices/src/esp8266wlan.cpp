#include <devices/esp8266wlan.hpp>
#include <hal/uart.hpp>
#include <console_print.hpp>
#include <cstring>
#include <cmath>
#include <functional>

using namespace drivers::uart;
using namespace devices::esp8266;
using namespace std::literals;

namespace console = utils::debug::console;

namespace {
#define ARRAY_LEN(x) ((sizeof(x)/sizeof(x[0])))

static constexpr std::string_view operation_succeed{"OK"};
static constexpr std::string_view operation_failed{"ERROR"};
static constexpr std::string_view operation_terminator{"\r\n"};

  class CwModeCommand
  {
    static constexpr std::string_view command_ = "AT+CWMODE=";
    devices::esp8266::Mode mode_;
  public:
    explicit CwModeCommand(const devices::esp8266::Mode& mode)
      : mode_{mode} {}

    void serialize(RingBuffer& rb) const
    {
      rb.write(command_.data(), command_.size());

      switch (mode_)
      {
      case devices::esp8266::Mode::Client:
        rb.write('1');
        break;
      
      case devices::esp8266::Mode::AccessPoint:
        rb.write('2');
        break;
      }

      rb.write(operation_terminator.data(), operation_terminator.size());
    }
  };


  static void handle_rx_end_wrapper(void* ctx, const size_t nbytes)
  {
    Esp8266Wlan* device = reinterpret_cast<Esp8266Wlan*>(ctx);
    device->handle_rx_end(nbytes);
  }
}



static volatile bool sync{true};
static volatile bool pending_operation{false};
static volatile bool response_ready{false};

static size_t expected_response_size = 0;

namespace devices::esp8266
{
  Esp8266Wlan::Esp8266Wlan(UartDriver* uart)
    : uart_{uart}
    , rx_rb_{rx_buffer_, RX_BUFFER_SIZE}
    , tx_rb_{tx_buffer_, TX_BUFFER_SIZE}
    {
      uart->rx_end_cb = handle_rx_end_wrapper;
      uart->rx_event_ctx = this;

      std::fill_n(rx_buffer_, RX_BUFFER_SIZE, '\0');
      std::fill_n(tx_buffer_, TX_BUFFER_SIZE, '\0');

      hal::uart::receive(uart_, rx_buffer_, RX_BUFFER_SIZE);
    }

  void Esp8266Wlan::reset()
  {

  }

  void Esp8266Wlan::set_mode(const Mode& mode)
  {
    console::print("[ESP8266] set_mode.\r\n");
    
    const auto command = CwModeCommand{mode};
    command.serialize(tx_rb_);

    execute_blocking_operation();
  }

  void Esp8266Wlan::execute_blocking_operation()
  {
    hal::uart::send(uart_, tx_buffer_, tx_rb_.capacity());

    while(!response_ready);

    //----------------
    //tmp
    auto needle = std::string_view{"AT+CWMODE"};
    //-----------------

    //Rolling hash
    //Compute hash 

    auto compute_hash = [](const std::string_view& sw, size_t base, size_t mod)
    {
      size_t hash = 0;
      for (size_t i = 0; i < sw.size(); ++i)
      {
        hash += sw[i] * std::pow(base, i);
      }
      return hash % mod;
    };

    constexpr uint32_t base = 7;
    constexpr uint32_t mod = 2147483647;

    //Fill haystack buffer 
    char haystack_buffer[64] = {"0"};
    std::generate_n(haystack_buffer, needle.size(), [&] { 
      const auto data = rx_rb_.read();
      rx_rb_.write(data);
      return data;
    });

    //Hashes
    size_t haystack_hash = compute_hash(std::string_view{haystack_buffer, needle.size()}, base, mod);
    const size_t needle_hash = compute_hash(needle, base, mod);

    //Drop & Add values
    size_t drop_idx = 0;
    size_t add_idx = needle.size();

    const uint32_t drop_power = std::pow(base, 0);
    const uint32_t add_power = std::pow(base, needle.size() - 1);

    auto drop = [&]()
    {
      haystack_hash -= haystack_buffer[drop_idx++] * drop_power;
      haystack_hash /= base;

      if (drop_idx == ARRAY_LEN(haystack_buffer) - needle.size())
      {
        for (size_t i = 0; i < needle.size(); ++i)
        {
          haystack_buffer[i] = haystack_buffer[drop_idx++];
        }
        drop_idx = 0;
        add_idx = needle.size();
      }
    };

    auto add = [&]()
    {
      const uint8_t data = rx_rb_.read();
      haystack_buffer[add_idx] = data;
      rx_rb_.write(data);
      haystack_hash += haystack_buffer[add_idx++] * add_power;
    };

    for (size_t i = 0; i < 20; i++)
    {
      if (haystack_hash == needle_hash)
      {
        console::print("Hash match.\n");

        break;
      }

      drop();
      add();
    }
  }

  void Esp8266Wlan::connect_wlan(const std::string_view uuid, const std::string_view password) {}
  
  //Handles
  void Esp8266Wlan::handle_rx_end(const size_t nbytes)
  {
    for (size_t i = 0; i < nbytes; i++)
    {
      rx_rb_.write(rx_buffer_[i]);
    }

    response_ready = true;

    // console::print(rx_rb_, rx_rb_.capacity());
  }

  void Esp8266Wlan::task()
  {
    
  }

}