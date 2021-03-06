#pragma once

#include <string>

enum Protocol
{
	HTTP,
	HTTPS
};

using Port = unsigned short;

class CHttpUrl
{
public:
	CHttpUrl(std::string const& url);
	CHttpUrl(std::string const& domain, std::string const& document,
		Protocol protocol = HTTP);
	CHttpUrl(std::string const& domain, std::string const& document,
		Protocol protocol, Port port);

	std::string GetURL() const;
	std::string GetDomain() const;
	std::string GetDocument() const;
	Protocol GetProtocol() const;
	Port GetPort() const;
    static std::string ProtocolToString(Protocol port);
	static std::string ProcessDocument(const std::string& document);

public:
	const Port MIN_PORT = 1;
	const Port MAX_PORT = USHRT_MAX;

private:
	std::string m_domain;
	std::string m_document;
	Protocol m_protocol;
	Port m_port;

private:
	Port GetDefaultProtocolPort() const;
	void ValidatePort(Port port) const;
};
