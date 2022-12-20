//
// Created by я on 19.12.2022.
//

#ifndef CSVPARSER_EXCEPTIONS_H
#define CSVPARSER_EXCEPTIONS_H

enum {
    WRONG_FILE = 2,
    BAD_ARGS,
    WRONG_DATA,
    WRONG_COUNT_OF_LINES
};

class Exceptions : std::exception {
private:
    int line = 0;
    int column = 0;
    int return_code;
    std::string error;
public:
    explicit Exceptions(int cur_line, int cur_column,int code, std::string er) : line(cur_line),
                                column(cur_column), return_code(code), error(er) {}

    explicit Exceptions(int code, std::string er) : return_code(code), error(er) {}

    int ret_code() {
        return this->return_code;
    }

    friend std::ostream& operator<<(std::ostream& out, const Exceptions& ex) {
        if (ex.line == 0 && ex.column == 0) return out << ex.error;
        else return out << ex.line << ":" << ex.column << " " << ex.error;
    }
};

#endif //CSVPARSER_EXCEPTIONS_H
