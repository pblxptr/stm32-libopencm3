#include <devices/esp8266wlan.hpp>
#include <hal/uart.hpp>
#include <console_print.hpp>
#include <cstring>

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

    uint8_t operation_buffer[64];
    auto operation_rb = RingBuffer{operation_buffer, ARRAY_LEN(operation_buffer)};
    std::fill(operation_rb.begin(), operation_rb.end(), '\0');

    while(!response_ready);

    const auto current_tail = rx_rb_.tail();
    const auto current_head = rx_rb_.head();
    while (current_head != current_tail)
    {
      if (operation_rb.head() == operation_rb.end() - 1)
      {
        operation_rb.write('\0');
        continue;
      }
      operation_rb.write(rx_rb_.read());
    }


    // hal::uart::send(uart_, tx_buffer_, tx_rb_.capacity());

    // char tmp_buff[64];

    // std::fill_n(tmp_buff, ARRAY_LEN(tmp_buff), '\0');

    // for (size_t i = 0; i < ARRAY_LEN(tmp_buff) - 1; ++i)
    // {
    //   //Check if buffer is not empty
    //   if (!rx_rb_.capacity())
    //     break;
      
    //   const auto data = rx_rb_.read();

    //   rx_rb_.tail();

    //   ///ASDACZXCASD\0ASDASDAT+CW
    //   //D=

    //   //Check if data is valid
    //   if (!(data >= 'A' && data <= 'Z' || data == ' '))
    //     continue;
      
    //   tmp_buff[i] = data;

    //   auto haystack = std::string_view{tmp_buff, ARRAY_LEN(tmp_buff) - 1};


    //   if (auto pos = haystack.find(std::string_view{"OK"}); pos != std::string_view::npos)
    //   {
    //     console::print("[ESP8266] Ok found.\r\n");
    //   }
    //   else if (auto pos = haystack.find(std::string_view{"ERROR"}); pos != std::string_view::npos)
    //   {
    //     console::print("[ESP8266] Error found.\r\n");
    //   }
    //   else 
    //   {
    //     console::print("[ESP8266] unkown response found.\r\n");
    //   }
    // }

    // tx_rb_.clear();
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