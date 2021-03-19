#include <iostream>
#include <boost/asio.hpp>
#include <vector>
#include <array>


using io_context = boost::asio::io_context;
using serial_port = boost::asio::serial_port;

void send_data(serial_port& sp, const std::vector<uint8_t>& data)
{
	std::cout << "Sending data: " << data.size() << '\n';

	auto bytes_sent = boost::asio::write(sp, boost::asio::buffer(data, data.size()));

	std::cout << "Number of bytes sent: " << bytes_sent  << "\n\n";
}

void wait_key()
{
		std::cout << "Click enter\n";

		std::cin.ignore();
}

std::vector<uint8_t> get_default_buffer(size_t len, uint8_t c)
{
		auto vec = std::vector<uint8_t>{};
		vec.resize(len);

		std::fill(vec.begin(), vec.end(), c);

		return vec;
}

std::vector<uint8_t> get_buffer_from_str(const std::string& str)
{
		return std::vector<uint8_t>(str.begin(), str.end());
}


int main(int argc, char** argv) 
{
		if (argc == 1)
		{
			std::cout << "Too few parameters.\n";
			return 1;
		}

    const char* dev_path = argv[1];
    auto io_context = boost::asio::io_context{};
	  auto sd = boost::asio::serial_port{io_context, dev_path};

		wait_key();
		send_data(sd, get_default_buffer(64, 'A'));


		wait_key();
		send_data(sd, get_default_buffer(32, 'B'));

		wait_key();
		send_data(sd, get_default_buffer(32, 'C'));

/**		
    auto buffer = std::array<std::uint8_t, 32>{};
    std::fill(buffer.begin(), buffer.end(), 'A');
    auto sd = boost::asio::serial_port{io_context, dev_path};

    auto nbytes = boost::asio::write(sd, boost::asio::buffer(buffer, buffer.size()));

    std::cout << "Number of bytes sent: " << nbytes << std::endl;

		std::cout << "Click enter\n";
		char c;
		std::cin >> c;
		auto buff2 = std::array<std::uint8_t, 32>{};
		std::fill(buff2.begin(), buff2.end(), 'B');
		
		auto nbytes2 = boost::asio::write(sd, boost::asio::buffer(buff2, buff2.size()));
		std::cout << "Number of bytes sent:" << nbytes2 << std::endl;

**/
    io_context.run();
		 
}   
