#include <iostream>
#include <string>

class StringGrandissent
{
    public :
        StringGrandissent() = default;
        StringGrandissent(const std::string& str) : str_(str) {}
        const std::string& getString() const
        {
            return str_;
        }
        void append(const std::string& str)
        {
            str_ += str;
        }
        friend std::ostream& operator<<(std::ostream& os, const StringGrandissent& sg);
    private :
        std::string str_;
};
std::ostream& operator<<(std::ostream& os, const StringGrandissent& sg)
{
    os << sg.str_;
    return os;
}
// faite sur vscode savais pas si fallait faire l'operator << mais quand meme faite et aussi le main pour tester
    int main()
{
    StringGrandissent sg("Hello");
    sg.append(", World!");
    std::cout << sg << std::endl;
    std::cout << "String length: " << sg.getString().length() << std::endl;
    return 0;
}
