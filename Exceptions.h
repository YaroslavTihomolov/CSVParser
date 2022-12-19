//
// Created by я on 19.12.2022.
//

#ifndef CSVPARSER_EXCEPTIONS_H
#define CSVPARSER_EXCEPTIONS_H

enum {
    WRONG_FILE = 2,
    BAD_ARGS,
    WRONG_DATA
};

class Exceptions : std::exception {
    int line;
    int column;
    int return_code;
    std::string error;
public:
    explicit Exceptions(int cur_line, int cur_column,int code, std::string er) : line(cur_line),
                                column(cur_column), return_code(code), error(er) {}

    int what_line() {
        return this->line;
    }

    std::string what_error() {
        return this->error;
    }

    int what_column() {
        return this->column;
    }

    int ret_code() {
        return this->return_code;
    }
};

#endif //CSVPARSER_EXCEPTIONS_H
