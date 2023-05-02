#include "Server.hpp"

#include <cstdlib>
#include <vector>
#include <iostream>
#include <string>
#include "../Constants.hpp"
#include "../Utils/Config/config.hpp"
#include "../Utils/Convert/tostring.hpp"
#include "../Utils/Convert/toarray.hpp"
#include "../Framework.hpp"
#include "../Utils/Convert/json_interprete.hpp"

#include "../Experiments/Experiment_1_00/EnvironmentLinear.hpp"

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

void http_server(tcp::acceptor& acceptor, tcp::socket& socket, Framework* &framework, ConfigRunner* &cr)
{
  acceptor.async_accept(socket,
      [&](beast::error_code ec)
      {
        if(!ec)
            std::make_shared<Server>(std::move(socket), framework, cr)->start();
        http_server(acceptor, socket, framework, cr);
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

Server::Server(tcp::socket socket, Framework* framework, ConfigRunner* cr)
    : socket_(std::move(socket))
{
    this->framework = framework;
    this->cr = cr;
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
            response_.set(http::field::server, "BioEvo");
            create_response();
            break;

        case http::verb::post:
            response_.result(http::status::ok);
            response_.set(http::field::server, "BioEvo");
            manage_post();
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

void Server::manage_post()
{
    std::vector<std::string> parsed_args = parse_args(request_.target());
    std::string url_target = parsed_args[0];

    if(url_target == "/bio-evo-api/instr")
    {
        std::string body_instructions = request_.body();  
        std::vector<boost::json::object> instrs = convert_to_objs(body_instructions);

        if(cr->is_executing())
        {
            response_.set(http::field::content_type, "text/plain");
            beast::ostream(response_.body())
                << "config runner is currently running";
        }
        else
        {
            cr->add_instructions(instrs);
            cr->continue_exec();
        }
    }
    else if(url_target == "/bio-evo-api/apply-config")
    {
        std::string config_name = request_.body();
        std::string instructions = get_config_content(config_name);
        std::vector<boost::json::object> instrs = convert_to_objs(instructions);
        
        if(cr->is_executing())
        {
            response_.set(http::field::content_type, "text/plain");
            beast::ostream(response_.body())
                << "config runner is currently running";
        }
        else
        {
            cr->add_instructions(instrs);
            cr->continue_exec();
        }
    }
}

void Server::create_response()
{
    // parse arguments
    std::vector<std::string> parsed_args = parse_args(request_.target());

    std::string url_target = parsed_args[0];
    
    if(url_target == "/bio-evo-api/info")
    {
        response_.set(http::field::content_type, "text/plain"); 

        // universes, environments and individuals        
        beast::ostream(response_.body())
            << framework->to_json();
    }
    else if(url_target == "/bio-evo-api/get-configs")
    {
        response_.set(http::field::content_type, "text/plain"); 

        // get configs names/paths        
        std::vector<std::string> configs = get_config_names();
        boost::json::array jconfigs;

        for(int i=0;i<configs.size();i++)
            jconfigs.emplace_back(configs[i]);

        beast::ostream(response_.body())
            << jconfigs;
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
