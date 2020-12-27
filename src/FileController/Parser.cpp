

Parser::Parser(Change ch) {
    ch_ = ch;
};

ParserForEditor::ParserForEditor(Change ch, FileStorage file) : Parser(ch){
    file_ = std::move(file);
};

std::vector<Symbol> ParserForEditor::parse() {
    std::vector<Symbol> file;
    Symbol text{};
    for (auto & symbol : file_.symbols){
        if (symbol.is_visible){
            text.symbol = symbol.symbol;
            text.symbol_id =symbol.id;
            file.push_back(text);
        }
    }
    return file;
}
//Не должно быть в своей библиотеке
//ParserToJson::ParserToJson(Change ch) : Parser(ch){}
//
//json ParserToJson::parse() {
//    json j =  {{"cmd", ch_.cmd},
//               {"fileId", ch_.fileId},
//               {"position",{
//                               {"symbolId", ch_.position.symbolId}}
//               },
//               {"newSymbolId", ch_.newSymbolId},
//               {"symbol", ch_.symbol}};
//    return j;
//}
//
//ParserFromJson::ParserFromJson(const json &j) {
//    j_ = j;
//}
//
//Change ParserFromJson::parse() {
//    Change m_ch {};
//    m_ch.cmd = j_["cmd"].get<Command>();
//    m_ch.fileId = j_["fileId"].get<size_t>();
//    m_ch.position = Position{j_["position"]["symbolId"].get<size_t>()};
//    m_ch.newSymbolId = j_["newSymbolId"].get<size_t>();
//    m_ch.symbol = j_["symbol"].get<char>();
//    return m_ch;
//}
//


