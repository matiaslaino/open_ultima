#pragma once

#include <tao/json.hpp>
#include <string>

using namespace std;

class Configuration {
public:
    static void init();

    static string getEgaOverworldTilesFilePath() {
        return _value.optional<string>("game_files_path").value() + "EGATILES.BIN";
    }

    static string getCgaOverworldTilesFilePath() {
        return _value.optional<string>("game_files_path").value() + "CGATILES.BIN";
    }

    static string getEgaTownFilePath() {
        return _value.optional<string>("game_files_path").value() + "EGATOWN.BIN";
    }

    static string getCgaTownFilePath() {
        return _value.optional<string>("game_files_path").value() + "CGATOWN.BIN";
    }

    static string getMapFilePath() {
        return _value.optional<string>("game_files_path").value() + "MAP.BIN";
    }

    static string getTownMapFilePath() {
        return _value.optional<string>("game_files_path").value() + "TCD.BIN";
    }

private:
    static tao::json::value _value;
};


