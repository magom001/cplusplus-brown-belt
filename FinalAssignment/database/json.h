#pragma once

#include <istream>
#include <ostream>
#include <map>
#include <set>
#include <unordered_map>
#include <map>
#include <string>
#include <variant>
#include <vector>
#include <memory>

namespace Json {
    class IStringifiable {
    public:
        virtual void Stringify(std::ostream&) = 0;
    };

    class Node : std::variant<std::vector<Node>,
            std::map<std::string, Node>,
            double,
            bool,
            std::string> {
    public:
        using variant::variant;

        const auto& AsArray() const {
            return std::get<std::vector<Node>>(*this);
        }
        const auto& AsMap() const {
            return std::get<std::map<std::string, Node>>(*this);
        }

        bool AsBool() const {
            return std::get<bool>(*this);
        }

        int AsInt() const {
            return static_cast<int>(std::get<double>(*this));
        }
        double AsDouble() const {
            return std::get<double>(*this);
        }
        const auto& AsString() const {
            return std::get<std::string>(*this);
        }
    };

    class Document {
    public:
        explicit Document(Node root);

        const Node& GetRoot() const;

    private:
        Node root;
    };

    Document Load(std::istream& input);


    std::ostream& Stringify(std::ostream& os, const std::string &);
    std::ostream& Stringify(std::ostream& os, double);
    std::ostream& Stringify(std::ostream& os, int);
    std::ostream& Stringify(std::ostream& os, std::shared_ptr<IStringifiable>);

    template<typename Iter>
    std::ostream& Stringify(std::ostream& os, Iter begin, Iter end) {
        os << '[';
        for (auto it = begin; it != end; ++it) {
            Stringify(os, *it);

            if (next(it) != end) {
                os << ',';
            }
        }
        os << ']';

        return os;
    }

}