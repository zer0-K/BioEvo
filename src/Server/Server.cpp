#include "Server.hpp"

#include <cstdlib>
#include <vector>
#include <iostream>
#include <string>
#include "../Constants.hpp"
#include "../Utils/Convert/tostring.hpp"

namespace beast = boost::beast;     // from <boost/beast.hpp>
namespace http = beast::http;       // from <boost/beast/http.hpp>
namespace net = boost::asio;        // from <boost/asio.hpp>
using tcp = net::ip::tcp;           // from <boost/asio/ip/tcp.hpp>

std::size_t request_count()
{
    static std::size_t count = 0;
    return ++count;
}

std::time_t now()
{
    return std::time(0);
}

void http_server(tcp::acceptor& acceptor, tcp::socket& socket)
{
  acceptor.async_accept(socket,
      [&](beast::error_code ec)
      {
          if(!ec)
              std::make_shared<Server>(std::move(socket))->start();
          http_server(acceptor, socket);
      });
}

std::vector<std::string> parse_args(std::string args)
{
    std::vector<std::string> parsed_args = std::vector<std::string>();
    size_t pos = 0;
    std::string arg;
    while ((pos = args.find('?')) != std::string::npos) {
        arg = args.substr(0, pos);
        parsed_args.push_back(arg); 
        args.erase(0, pos+1);
    }
    parsed_args.push_back(args);

    return parsed_args;
}

Server::Server(tcp::socket socket)
    : socket_(std::move(socket))
{
    this->framework = new Framework();
}

void Server::start()
{
    read_request();
    check_deadline();
}

void Server::read_request()
{
    auto self = shared_from_this();

    http::async_read(
        socket_,
        buffer_,
        request_,
        [self](beast::error_code ec,
            std::size_t bytes_transferred)
        {
            boost::ignore_unused(bytes_transferred);
            if(!ec)
                self->process_request();
        }
    );
}

void Server::process_request()
{
    response_.version(request_.version());
    response_.keep_alive(false);
    response_.set("Access-Control-Allow-Origin", "*");

    switch(request_.method())
    {
        case http::verb::get:
            response_.result(http::status::ok);
            response_.set(http::field::server, "Beast");
            create_response();
            break;

        default:
            // We return responses indicating an error if
            // we do not recognize the request method.
            response_.result(http::status::bad_request);
            response_.set(http::field::content_type, "text/plain");
            beast::ostream(response_.body())
                << "Invalid request-method '"
                << std::string(request_.method_string())
                << "'";
            break;
    }

    write_response();
}

void Server::create_response()
{
    // parse arguments
    std::vector<std::string> parsed_args = parse_args(request_.target());
    
    if(parsed_args[0] == "/bio-evo-api/time")
    {
        response_.set(http::field::content_type, "text/plain"); 

        beast::ostream(response_.body())
            <<  "test text";
    }
    else if(parsed_args[0] == "/bio-evo-api/info")
    {
        response_.set(http::field::content_type, "text/plain"); 

        // universes, environments and individuals        
        beast::ostream(response_.body())
            << "{'universes':"
            << convert_str(UNIVERSE_NAMES)
            << ", ";

        beast::ostream(response_.body())
            << "'environments':"
            << convert_str(ENV_NAMES_BY_UNIVERSE)
            << ", ";

        beast::ostream(response_.body())
            << "'individuals':"
            << convert_str(INDIVIDUAL_NAMES_BY_ENV)
            << "}";
    }
    else
    {
        response_.result(http::status::not_found);
        response_.set(http::field::content_type, "text/plain");
        beast::ostream(response_.body()) << "File not found\r\n";
    }
}

void Server::write_response()
{
    auto self = shared_from_this();

    response_.content_length(response_.body().size());

    http::async_write(
        socket_,
        response_,
        [self](beast::error_code ec, std::size_t)
        {
            self->socket_.shutdown(tcp::socket::shutdown_send, ec);
            self->deadline_.cancel();
        }
    );
}

void Server::check_deadline()
{
    auto self = shared_from_this();

    deadline_.async_wait(
        [self](beast::error_code ec)
        {
            if(!ec)
            {
                // Close socket to cancel any outstanding operation.
                self->socket_.close(ec);
            }
        }
    );
}
