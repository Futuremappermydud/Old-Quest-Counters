    #include "../include/Main.hpp"

#include "../extern/beatsaber-hook/shared/utils/il2cpp-utils.hpp"
#include "../extern/beatsaber-hook/shared/utils/il2cpp-functions.hpp"
#include "../extern/beatsaber-hook/shared/utils/utils.h"
#include "../extern/BeatSaberQuestCustomUI-master/shared/customui.hpp"

using namespace il2cpp_utils;
using namespace CustomUI;

static ModInfo modInfo;
bool _360 = false;

Configuration& getConfig() {
  static Configuration configuration(modInfo);
  return configuration;
}

int oneSaberType;

bool NoHud = false;

int Notes;
std::string JSON = R"({"metadata":{"difficulties":{"easy":true,"expert":false,"expertPlus":true,"hard":false,"normal":false},"duration":201,"characteristics":[{"difficulties":{"easy":null,"expert":null,"expertPlus":{"duration":529.933349609375,"length":198,"njs":21,"njsOffset":-0.30000001192092896,"bombs":43,"notes":1170,"obstacles":19},"hard":null,"normal":null},"name":"Standard"},{"difficulties":{"easy":{"duration":0,"length":0,"njs":16,"njsOffset":0,"bombs":0,"notes":0,"obstacles":0},"expert":null,"expertPlus":null,"hard":null,"normal":null},"name":"Lightshow"}],"levelAuthorName":"ETAN","songAuthorName":"Reol","songName":"Utena","songSubName":"","bpm":160},"stats":{"downloads":11119,"plays":0,"downVotes":48,"upVotes":326,"heat":1459.8648634,"rating":0.8092436735206341},"description":"Building Blocks 2020 1st Place Entry\n\nSubmission #48\n\nThank you for playing!\n\nuse CHROMA for cool lights and such\n\nPreview: https://youtu.be/zrnWfI5xpwI","deletedAt":null,"_id":"5ed069402586060006ab0bdf","key":"abc4","name":"Reol - Utena","uploader":{"_id":"5cff0b7798cc5a672c855775","username":"etan"},"hash":"0cb1b38c96b71676db359a95353dca50ba54b183","uploaded":"2020-05-29T01:45:36.835Z","directDownload":"/cdn/abc4/0cb1b38c96b71676db359a95353dca50ba54b183.zip","downloadURL":"/api/download/key/abc4","coverURL":"/cdn/abc4/0cb1b38c96b71676db359a95353dca50ba54b183.jpg"})";

MAKE_HOOK_OFFSETLESS(UIStart, void, Il2CppObject* self) {
    UIStart(self);
    if(NoHud) return;
    if(getConfig().config["Accuracy Counter"].GetBool())
    {
        Accuracy_Start(self);
    }
    if(getConfig().config["Notes Left / Note Percentage"].GetBool())
    {
        NotesLeft_Start(self);
    }
    if(getConfig().config["Missed Notes Counter"].GetBool())
    {
        Miss_Start(self);
    }
    if(getConfig().config["Hit Notes Counter"].GetBool())
    {
        Hit_Start(self);
    }
    if(getConfig().config["Saber Speed Counter"].GetBool())
    {
        Speed_Start(self);
    }
    if(getConfig().config["Personal Best Counter"].GetBool())
    {
        PB_Start(self);
    }
    if(getConfig().config["Hit Bomb Counter"].GetBool())
    {
        Bomb_Start(self);
    }
    if(getConfig().config["Walls Left / Wall Percentage"].GetBool())
    {
        WallsLeft_Start(self);
    }
    if(getConfig().config["Play Count(er)"].GetBool())
    {
        PC_Start(self);
    }
}

MAKE_HOOK_OFFSETLESS(FinishScore, void, Il2CppObject* self, Il2CppObject* swingRatingCounter) {
    FinishScore(self, swingRatingCounter);
    if(NoHud) return;
    Accuracy_FinishScore();
}

MAKE_HOOK_OFFSETLESS(RawScore, void, Il2CppObject* noteCutInfo, int* beforeCutRawScore, int* afterCutRawScore, int* cutDistanceRawScore) {
    RawScore(noteCutInfo, beforeCutRawScore, afterCutRawScore, cutDistanceRawScore);
    if(NoHud) return;
    Accuracy_RawScore(noteCutInfo, beforeCutRawScore, afterCutRawScore, cutDistanceRawScore);
}

MAKE_HOOK_OFFSETLESS(SongStart, void, Il2CppObject* self, Il2CppObject* difficultyBeatmap, Il2CppObject* overrideEnvironmentSettings, Il2CppObject* overrideColorScheme, Il2CppObject* gameplayModifiers, Il2CppObject* playerSpecificSettings, Il2CppObject* practiceSettings, Il2CppString* backButtonText, bool useTestNoteCutSoundEffects) {
    NotesLeft_GetNotes(difficultyBeatmap);
    WallsLeft_GetWalls(difficultyBeatmap);
    NoHud = *GetPropertyValue<bool>(playerSpecificSettings, "noTextsAndHuds");
    SongStart(self, difficultyBeatmap, overrideEnvironmentSettings, overrideColorScheme, gameplayModifiers, playerSpecificSettings, practiceSettings, backButtonText, useTestNoteCutSoundEffects);
}

MAKE_HOOK_OFFSETLESS(HandleNoteWasMissedEvent, void, Il2CppObject* self, Il2CppObject* noteController) {
    HandleNoteWasMissedEvent(self, noteController);
    if(NoHud) return;
    if(NotesLeft_CheckOk_Miss(noteController))
    {
        NotesLeft_Update();
        Miss_Update();
    }
}   
MAKE_HOOK_OFFSETLESS(HandleNoteWasCutEvent, void, Il2CppObject* self, Il2CppObject* noteController, Il2CppObject* noteCutInfo)
{
    HandleNoteWasCutEvent(self, noteController, noteCutInfo);
    if(NoHud) return;
    //Hit Counter
    auto NoteData = *il2cpp_utils::RunMethod<Il2CppObject*>( noteController, "get_noteData");
    int NoteType = *il2cpp_utils::RunMethod<int>( NoteData, "get_noteType");
    bool AllOkee = *GetPropertyValue<bool>(noteCutInfo, "allIsOK");
    if(NoteType == 0 || NoteType == 1)
    {
        NotesLeft_Update();
        if(AllOkee)
        {
            Hit_Update();
        }
        else
        {
            Miss_Update();
        }
    }
    if(NoteType == 3)
    {
        Bomb_Update();
    }
}
MAKE_HOOK_OFFSETLESS(Speed, void, Il2CppObject* self)
{
    oneSaberType = *GetFieldValue<int>(self, "_oneSaberType");
    Speed(self);
    Il2CppObject* LeftSaber = *GetFieldValue(self, "_leftSaber");
    float LeftSpeed = *GetPropertyValue<float>(LeftSaber, "bladeSpeed");
    Il2CppObject* RightSaber = *GetFieldValue(self, "_rightSaber");
    float RightSpeed = *GetPropertyValue<float>(RightSaber, "bladeSpeed");
    Speed_Update(LeftSpeed, RightSpeed);
}

MAKE_HOOK_OFFSETLESS(CheckVersion, void, Il2CppObject* self, bool firstActivation, int activationType)
{
    CheckVersion(self, firstActivation, activationType);
    
}

MAKE_HOOK_OFFSETLESS(StartVersion, void, Il2CppObject* self, bool firstActivation, int activationType)
{
    StartVersion(self, firstActivation, activationType);
    Update_Start(self);
    Update_Update();
}

MAKE_HOOK_OFFSETLESS(StandardLevelDetailView_RefreshContent, void, Il2CppObject * self) {
    StandardLevelDetailView_RefreshContent(self);
    Il2CppObject* Level = *GetFieldValue(self, "_level");
    Il2CppString* LevelID = *GetPropertyValue<Il2CppString*>(Level, "levelID");

    Il2CppObject* SelectedBeatmapDifficulty = *GetFieldValue(self, "_selectedDifficultyBeatmap");
    int Difficulty = *GetPropertyValue<int>(SelectedBeatmapDifficulty, "difficulty");
    Il2CppObject* beatMapData = *GetPropertyValue(SelectedBeatmapDifficulty, "beatmapData");
    Il2CppObject* parentDifficultyBeatmapSet = *GetPropertyValue(SelectedBeatmapDifficulty, "parentDifficultyBeatmapSet");
    Il2CppObject* beatmapCharacteristic = *GetPropertyValue(parentDifficultyBeatmapSet, "beatmapCharacteristic");

    Il2CppObject* PlayerData = *GetFieldValue(self, "_playerData");
    Il2CppObject* playerLevelStatsData = *RunMethod(PlayerData, "GetPlayerLevelStatsData", LevelID, Difficulty, beatmapCharacteristic);
    currentScore = *GetPropertyValue<int>(playerLevelStatsData, "highScore");
    Plays = *GetPropertyValue<int>(playerLevelStatsData, "playCount");
    Notes = *GetPropertyValue<int>(beatMapData, "notesCount");
    currentPercentage = calculatePercentage(calculateMaxScore(Notes), currentScore);
}

MAKE_HOOK_OFFSETLESS(SpawnObstacle, void, Il2CppObject* self, Il2CppObject* obstacleData)
{
    SpawnObstacle(self, obstacleData);
    WallsLeft_Update();
}

MAKE_HOOK_OFFSETLESS(RelativeScoreAndImmediateRankCounter_Update, void, Il2CppObject* self, int score, int modifiedScore, int maxPossibleScore, int maxPossibleModifiedScore)
{
    RelativeScoreAndImmediateRankCounter_Update(self, score, modifiedScore, maxPossibleScore, maxPossibleModifiedScore);
    float LMAO = (float)score / (float)maxPossibleScore;
    PB_Update(LMAO * 100.0f);
}

MAKE_HOOK_OFFSETLESS(StartConfigUI, void, Il2CppObject* self)
{
    StartConfigUI(self);
    SettingsUI_Start(self);
}

MAKE_HOOK_OFFSETLESS(LevelListTableCell_SetDataFromLevelAsync, void, Il2CppObject* self, Il2CppObject* level, bool isFavorite) {
    LevelListTableCell_SetDataFromLevelAsync(self, level, isFavorite);
    Il2CppObject* _authorText = *GetFieldValue(self, "_songNameText");
    rapidjson::Document d;
    d.Parse(JSON.c_str());
    int upvotes = d["stats"]["upVotes"].GetInt();
    int downvotes = d["stats"]["downVotes"].GetInt();
    std::string Final = to_utf8(csstrtostr(*GetPropertyValue<Il2CppString*>(_authorText, "text")));
    Il2CppString* endstring = createcsstr(Final + "<size=65%>\nUpvotes: " + std::to_string(upvotes) + "\nDownvotes: " + std::to_string(downvotes));
    SetPropertyValue(_authorText, "richText", true);
    RunMethod(_authorText, "SetText", endstring);
}

MAKE_HOOK_OFFSETLESS(LevelCollectionTableView_Cellsize, float, Il2CppObject* self) {
    SetFieldValue(self, "_cellHeight", 10.0f);
    return LevelCollectionTableView_Cellsize(self);
}

extern "C" void setup(ModInfo& info) {
    info.id = "QuestCounters";
    info.version = "1.2.5";
    modInfo = info;
    // Create logger
    static std::unique_ptr<const Logger> ptr(new Logger(info));
    logger = ptr.get();
    logger->info("Completed setup!");
    // We can even check information specific to the modloader!
    logger->info("Modloader name: %s", Modloader::getInfo().name.c_str());
    // Create config
    getConfig();
    getConfig().Load();
    // Can use getConfig().config to modify the rapidjson document
    getConfig().Write();
}

extern "C" void load() {
    if(!LoadConfig())
    {
        SaveConfig();
    }
    il2cpp_functions::Init();
    INSTALL_HOOK_OFFSETLESS(RawScore, il2cpp_utils::FindMethodUnsafe("", "ScoreModel", "RawScoreWithoutMultiplier", 4));
    INSTALL_HOOK_OFFSETLESS(FinishScore, il2cpp_utils::FindMethodUnsafe("", "CutScoreBuffer", "HandleSwingRatingCounterDidFinishEvent", 1));
    INSTALL_HOOK_OFFSETLESS(UIStart, il2cpp_utils::FindMethodUnsafe("", "ScoreUIController", "Start", 0));
    INSTALL_HOOK_OFFSETLESS(SongStart, il2cpp_utils::FindMethodUnsafe("", "StandardLevelScenesTransitionSetupDataSO", "Init", 8));
    INSTALL_HOOK_OFFSETLESS(HandleNoteWasMissedEvent, il2cpp_utils::FindMethodUnsafe("", "ScoreController", "HandleNoteWasMissedEvent", 1));
    INSTALL_HOOK_OFFSETLESS(HandleNoteWasCutEvent, il2cpp_utils::FindMethodUnsafe("", "ScoreController", "HandleNoteWasCutEvent", 2));
    INSTALL_HOOK_OFFSETLESS(CheckVersion, il2cpp_utils::FindMethodUnsafe("", "HealthWarningFlowCoordinator", "DidActivate", 2));
    INSTALL_HOOK_OFFSETLESS(StartVersion, il2cpp_utils::FindMethodUnsafe("", "MainMenuViewController", "DidActivate", 2));
    INSTALL_HOOK_OFFSETLESS(Speed, il2cpp_utils::FindMethodUnsafe("", "SaberManager", "Update", 0));
    INSTALL_HOOK_OFFSETLESS(StandardLevelDetailView_RefreshContent, FindMethodUnsafe("", "StandardLevelDetailView", "RefreshContent", 0));
    INSTALL_HOOK_OFFSETLESS(SpawnObstacle, FindMethodUnsafe("", "BeatmapObjectSpawnController", "SpawnObstacle", 1));
    INSTALL_HOOK_OFFSETLESS(RelativeScoreAndImmediateRankCounter_Update, FindMethodUnsafe("", "RelativeScoreAndImmediateRankCounter", "UpdateRelativeScoreAndImmediateRank", 4));
    INSTALL_HOOK_OFFSETLESS(StartConfigUI, FindMethodUnsafe("", "PauseMenuManager", "Start", 0));
    INSTALL_HOOK_OFFSETLESS(LevelListTableCell_SetDataFromLevelAsync, FindMethodUnsafe("", "LevelListTableCell", "SetDataFromLevelAsync", 2));
    //INSTALL_HOOK_OFFSETLESS(LevelCollectionTableView_Cellsize, FindMethodUnsafe("", "LevelCollectionTableView", "CellSize", 0));
}
/*
class LightData
{
    public: 
    int Time;
    int Type;
    int Value;
    rapidjson::GenericObject<false, rapidjson::Value> CustomData;
    LightData(int value, int type, int time, auto Data)
    {
        Time = time;
        Type = type;

    };
};
Array<LightData> GetLightData(std::string BeatMapJson)
{
    Array<float > arr;

}
std::string GetBeatmaps(std::string songID, std::string InfoJson)
{
    static rapidjson::Document d;
    d.Parse(InfoJson.c_str());
    auto arr = d["_difficultyBeatmapSets"].GetArray();
    auto arr2 = arr[0]["_difficultyBeatmaps"].GetArray();
    auto fileName = arr2[0]["_beatmapFilename"].GetString();
    return GetInfoJson(songID, "/" + fileName);
}
std::string GetInfoJson(std::string songID, std::string FileName = "/info.dat")
{
    std::string songPath = "/sdcard/BMBFData/CustomSongs/" + songID + FileName;
    std::string myText;
    std::ifstream SongFile(songPath);
    std::string finalstr = "";
    while (getline(SongFile, myText)) {
        finalstr += myText;
    }
    if (finalstr == "") {
        finalstr = "invalid";
    }
    SongFile.close();
    return GetBeatmaps(songID, finalstr);
}
*/