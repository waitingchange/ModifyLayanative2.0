#pragma once

#include <string>
#include <vector>
#include <stdint.h>

class Uri
{
public:
    /**
     * Parse a Uri from a string.  Throws std::invalid_argument on parse error.
     */
    static Uri parse(const std::string& str);

    /** Default constructor */
    Uri();

    /** Copy constructor */
    Uri(const Uri& o);

    /** Move constructor */
    Uri(Uri&& o);

    /** Copy assignment */
    Uri& operator=(const Uri& o);

    /** Move assignment */
    Uri& operator=(Uri&& o);

    /** Checks whether two Uri instances contain the same values */
    bool operator==(const Uri& o) const;

    /** Checks wether it's a valid URI */
    bool isValid() const { return _isValid; }

    /** Checks whether it's a SSL connection */
    bool isSecure() const { return _isSecure; }

    /** Gets the scheme name for this URI. */
    const std::string& getScheme() const { return _scheme; }

    /** Gets the user name with the specified URI. */
    const std::string& getUserName() const { return _username; }

    /** Gets the password with the specified URI. */
    const std::string& getPassword() const { return _password; }
    /**
     * Get host part of URI. If host is an IPv6 address, square brackets will be
     * returned, for example: "[::1]".
     */
    const std::string& getHost() const { return _host; }
    /**
     * Get host part of URI. If host is an IPv6 address, square brackets will not
     * be returned, for exmaple "::1"; otherwise it returns the same thing as
     * getHost().
     *
     * getHostName() is what one needs to call if passing the host to any other tool
     * or API that connects to that host/port; e.g. getaddrinfo() only understands
     * IPv6 host without square brackets
     */
    const std::string& getHostName() const { return _hostName; }

    /** Gets the port number of the URI. */
    uint16_t getPort() const { return _port; }

    /** Gets the path part of the URI. */
    const std::string& getPath() const { return _path; }

    /// Gets the path, query and fragment parts of the URI.
    const std::string& getPathEtc() const { return _pathEtc; }

    /** Gets the query part of the URI. */
    const std::string& getQuery() const { return _query; }

    /** Gets the fragment part of the URI */
    const std::string& getFragment() const { return _fragment; }

    /** Gets the authority part (userName, password, host and port) of the URI.
     * @note If the port number is a well-known port
     *      number for the given scheme (e.g., 80 for http), it
     *      is not included in the authority.
     */
    const std::string& getAuthority() const { return _authority; }

    /** Gets a string representation of the URI. */
    std::string toString() const;

    /**
    * Get query parameters as key-value pairs.
    * e.g. for URI containing query string:  key1=foo&key2=&key3&=bar&=bar=
    * In returned list, there are 3 entries:
    *     "key1" => "foo"
    *     "key2" => ""
    *     "key3" => ""
    * Parts "=bar" and "=bar=" are ignored, as they are not valid query
    * parameters. "=bar" is missing parameter name, while "=bar=" has more than
    * one equal signs, we don't know which one is the delimiter for key and
    * value.
    *
    * Note, this method is not thread safe, it might update internal state, but
    * only the first call to this method update the state. After the first call
    * is finished, subsequent calls to this method are thread safe.
    *
    * @return  query parameter key-value pairs in a vector, each element is a
    *          pair of which the first element is parameter name and the second
    *          one is parameter value
    */
    const std::vector<std::pair<std::string, std::string>>& getQueryParams();

    /** Clears all parts of the URI. */
    void clear();

private:
    bool doParse(const std::string& str);

    bool _isValid;
    bool _isSecure;
    std::string _scheme;
    std::string _username;
    std::string _password;
    std::string _host;
    std::string _hostName;
    bool _hasAuthority;
    uint16_t _port;
    std::string _authority;
    std::string _pathEtc;
    std::string _path;
    std::string _query;
    std::string _fragment;
    std::vector<std::pair<std::string, std::string>> _queryParams;
};
