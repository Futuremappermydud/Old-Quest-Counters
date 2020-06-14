#include "../include/mod_interface.hpp"

#include <unordered_set>

#include "../extern/beatsaber-hook/shared/utils/il2cpp-utils.hpp"  
#include "../extern/beatsaber-hook/shared/utils/il2cpp-functions.hpp"  
#include "../extern/BeatSaberQuestCustomUI-master/shared/customui.hpp"
#include "../extern/beatsaber-hook/shared/utils/utils.h"  
#include "../extern/beatsaber-hook/shared/config/rapidjson-utils.hpp"
#include "../extern/beatsaber-hook/shared/config/config-utils.hpp"

using namespace il2cpp_utils;
using namespace CustomUI;

Configuration& getConfig();
static const Logger* logger;
static struct Config_t {
    bool Missed = true;
    bool Hits = true;
    bool NotesLeft = true;
    bool Acc = true;
    bool Speed = true;
    bool PB = true;
    bool BombHits = true;
    bool WallsLeft = true;
    bool playCount = true;
    std::string HIT_HexColor = "#00FF00";
} Config;



extern void SaveConfig();
extern bool LoadConfig();

//Accuracy
void Accuracy_Start(Il2CppObject* self);

void Accuracy_FinishScore();

void Accuracy_RawScore(Il2CppObject* noteCutInfo, int* beforeCutRawScore, int* afterCutRawScore, int* cutDistanceRawScore);

//Notes Left
void NotesLeft_GetNotes(Il2CppObject* difficultyBeatmap);

void NotesLeft_Start(Il2CppObject* self);

bool NotesLeft_CheckOk_Miss(Il2CppObject* noteController);

void NotesLeft_Update();

//Missed Notes
void Miss_Start(Il2CppObject* self);

void Miss_Update();

//Hit Notes
void Hit_Start(Il2CppObject* self);

void Hit_Update();

//Hit Bombs
void Bomb_Start(Il2CppObject* self);

void Bomb_Update();

//Speed
void Speed_Start(Il2CppObject* self);

void Speed_Update(float LeftSpeed, float RightSpeed);

//Update
extern std::string Ver;
extern std::string LATESTVer;
void Update_Update();
void Update_Start(Il2CppObject* self);

//PB
void PB_Start(Il2CppObject* self);
void PB_Update(float percent);
int calculateMaxScore(int blockCount);
float calculatePercentage(int maxScore, int resultScore);
extern float currentPercentage;
extern int currentScore;
extern int ModdedScore;

//Walls Left
void WallsLeft_Update();

void WallsLeft_GetWalls(Il2CppObject* difficultyBeatmap);

void WallsLeft_Start(Il2CppObject* self);

//Play Count
extern int Plays;

void PC_Start(Il2CppObject* self);


//Misc Vars
extern bool _360;
extern int Notes;
extern int WallsCount;
extern int oneSaberType;
extern bool oneSaber;


//UI
void SettingsUI_Start(Il2CppObject* self);