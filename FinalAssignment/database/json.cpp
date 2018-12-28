#include "json.h"
#include <sstream>

using namespace std;

namespace Json {

    Document::Document(Node root) : root(move(root)) {
    }

    const Node &Document::GetRoot() const {
        return root;
    }

    Node LoadNode(istream &input);

    Node LoadArray(istream &input) {
        vector<Node> result;

        for (char c; input >> c && c != ']';) {
            if (c != ',') {
                input.putback(c);
            }
            result.push_back(LoadNode(input));
        }

        return Node(move(result));
    }

    Node LoadBool(istream &input) {
        char c;
        input >> c;
        if (c == 't') {
            input.ignore(3);
            return Node(true);
        } else {
            input.ignore(4);
            return Node(false);
        }
    }

    Node LoadNumber(istream &input) {
        double result;
        input >> result;
        return Node(result);
    }

    Node LoadString(istream &input) {
        string line;
        getline(input, line, '"');
        return Node(move(line));
    }

    Node LoadDict(istream &input) {
        map<string, Node> result;

        for (char c; input >> c && c != '}';) {
            if (c == ',') {
                input >> c;
            }

            string key = LoadString(input).AsString();
            input >> c;
            result.emplace(move(key), LoadNode(input));
        }

        return Node(move(result));
    }

    Node LoadNode(istream &input) {
        char c;
        input >> c;

        if (c == '[') {
            return LoadArray(input);
        } else if (c == '{') {
            return LoadDict(input);
        } else if (c == '"') {
            return LoadString(input);
        } else if (c == 't' || c == 'f') {
            input.putback(c);
            return LoadBool(input);
        } else {

            input.putback(c);
            return LoadNumber(input);
        }
    }

    Document Load(istream &input) {
        return Document{LoadNode(input)};
    }

    std::ostream& Stringify(std::ostream& os, const std::string &s) {
        os << '"' << s << '"';
        return os;
    }

    std::ostream& Stringify(std::ostream& os, double d) {
        os << d;
        return os;
    }

    std::ostream& Stringify(std::ostream& os, int d) {
        os << d;
        return os;
    }

    std::ostream &Stringify(std::ostream &os, shared_ptr<IStringifiable> obj) {
        obj->Stringify(os);
        return os;
    }

}