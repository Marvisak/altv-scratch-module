#include "resource.h"
#include <fstream>

std::shared_ptr<Block> resolveBlock(BlockTable &blocktable, nlohmann::json blocks, std::string id);
std::shared_ptr<Block> resolveShadow(BlockTable &blocktable, nlohmann::json shadow);
std::shared_ptr<StackOfBlocks> resolveStackOfBlocks(BlockTable &blocktable, nlohmann::json blocks, std::string start);

void RunScratchFile(const std::string& path) {

    std::ifstream scrapefile(path);
    nlohmann::json scrapejson;
    scrapefile >> scrapejson;

    BlockTable scrapestate(scrapejson["ids"].get<int>()+2);

    scrapestate.setIndex(scrapestate.size()-2,std::make_shared<Variable>()); // Answer Variable
    scrapestate.setIndex(scrapestate.size()-1,std::make_shared<GlobalTimer>()); // Global Timer

    for (auto& variable:scrapejson["container"]["variables"].items()) {
        std::shared_ptr<Variable> v = std::make_shared<Variable>(scrapejson["container"]["variables"][variable.key()].get<std::string>());
        scrapestate.setIndex(std::stoi(variable.key()), v);
    }

    for (auto& list:scrapejson["container"]["lists"].items()) {
        std::shared_ptr<List> l = std::make_shared<List>(scrapejson["container"]["lists"][list.key()].get<std::vector<std::string>>());
        scrapestate.setIndex(std::stoi(list.key()), l);
    }

    for (auto& id:scrapejson["build_order"].items()) {
        resolveBlock(scrapestate, scrapejson["blocks"], id.value());
    }

    std::shared_ptr<StackOfBlocks> mainstack = resolveStackOfBlocks(scrapestate, scrapejson["blocks"], scrapejson["start"].get<std::string>());

    try
    {
        mainstack->execAll();
    }
    catch(StopBlockCalledException& e) {}
    catch(StandardInputException& e) {}
}

void CompileScratchFile(const char* folder, const char* main) {
    PyObject* scrapec = PyImport_ImportModule("scrapec");
    PyObject* func = PyObject_GetAttrString(scrapec, "compile");
    PyObject* args = PyTuple_New(2);
    PyObject* pyPath2 = PyUnicode_FromString(folder);
    PyObject* pyFolder = PyUnicode_FromString(main);
    PyTuple_SetItem(args, 0, pyPath2);
    PyTuple_SetItem(args, 1, pyFolder);
    PyObject_CallObject(func, args);
}

bool ScratchResource::Start() {
    auto path = resource->GetPath().ToString();
    auto main = resource->GetMain().ToString();
    auto cacheFile = path + "\\" + "cache" + "\\" + main;
    CompileScratchFile(path.c_str(), main.c_str());
    RunScratchFile(cacheFile);
    return true;
}