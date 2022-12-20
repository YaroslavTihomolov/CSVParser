#include "Parser.h"

Parser::Parser(int argc, char** argv) {
    po::options_description desc("Generate parameters");
    std::string tmp;
    desc.add_options()
            ("lines_separator", po::value<std::string>(&tmp), "--lines_separator=[symbol]")
            ("column_separator", po::value<char>(&column_separator), "--column_separator=[symbol]")
            ("shielding", po::value<char>(&shielding), "--shielding=[symbol]")
            ;
    try {
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);
    } catch(po::error &e) {
        throw Exceptions(BAD_ARGS, e.what());
    }

    if (tmp == "\\n")
        lines_separator = '\n';
    else
        std::istringstream(tmp) >> lines_separator;
}
