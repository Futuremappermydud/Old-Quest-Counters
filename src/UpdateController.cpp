#include "include/Main.hpp"
#include "../extern/BeatSaberQuestCustomUI-master/shared/customui.hpp"
using std::string;

string URL = "https://raw.githubusercontent.com/Futuremappermydud/Quest-Counters/master/ASSETS/ver.txt";

Il2CppObject* WebRequestAPI = nullptr;
Il2CppObject* DownloadHandler = nullptr;
Il2CppObject* WebRequestAsyncOp = nullptr;
Il2CppString* JsonStr = nullptr; 

std::string Ver = "1.2.5";
std::string LATESTVer = "LOADING";

CustomUI::TextObject VersionText;

void CompletedWebRequest()
{
    DownloadHandler = CRASH_UNLESS(RunMethod<Il2CppObject*>(WebRequestAPI, "get_downloadHandler"));
 
    JsonStr = CRASH_UNLESS(RunMethod<Il2CppString*>(DownloadHandler, FindMethodUnsafe("UnityEngine.Networking", "DownloadHandler", "GetText", 0)));
 
    string requestCompleteText = to_utf8(csstrtostr(JsonStr));
    logger->debug("Text: %s", requestCompleteText.c_str());
    LATESTVer = requestCompleteText;
    VersionText.set("<color=#FFD700>Quest Counters</color>\nYour Version: " + Ver + "\nRecent Version: " + LATESTVer);
}
 
void WebRequest()
{
    WebRequestAPI = CRASH_UNLESS(RunMethod(GetClassFromName("UnityEngine.Networking", "UnityWebRequest"), "Get", createcsstr(URL)));
 
    CRASH_UNLESS(RunMethod(WebRequestAPI, FindMethodUnsafe("UnityEngine.Networking", "UnityWebRequest", "SetRequestHeader", 2), createcsstr("User-Agent"), createcsstr("Quest Counters / " + Ver)));
    WebRequestAsyncOp = CRASH_UNLESS(RunMethod(WebRequestAPI, "SendWebRequest"));  
 
    // I replaced the way of making the action as I believe it crashes because of the field thingy so now it finds the method and then uses the field from that method.    
    const MethodInfo* addCompletedMethod = CRASH_UNLESS(il2cpp_utils::FindMethodUnsafe(WebRequestAsyncOp, "add_completed", 1));
    auto action = CRASH_UNLESS(il2cpp_utils::MakeAction(addCompletedMethod, 0, (Il2CppObject*)nullptr, CompletedWebRequest));
    CRASH_UNLESS(il2cpp_utils::RunMethod(WebRequestAsyncOp, addCompletedMethod, action));
}

void Update_Update()
{
	//WebRequest();
}

void Update_Start(Il2CppObject* self)
{
	//Destroy Object if the Object isnt just now created
    if (VersionText.gameObj != nullptr)
    {
        RunMethod(GetClassFromName("UnityEngine", "Object"), "Destroy", VersionText.gameObj);
    }
    //Get Campaign Button Transform
    Il2CppObject* CampaignB = CRASH_UNLESS(GetFieldValue(self, "_campaignButton"));
    Il2CppObject* CampaignBTransform = CRASH_UNLESS(RunMethod<Il2CppObject*>(CampaignB, "get_transform"));
    //Set Values
    VersionText.fontSize = 5.0F;
    VersionText.sizeDelta = {0, -60 };
    VersionText.parentTransform = CampaignBTransform;
    //Set Text
    VersionText.text = "<color=#FFD700>Quest Counters</color>\nYour Version: " + Ver;// + "\nRecent Version: " + LATESTVer;
    //Create
    CRASH_UNLESS(VersionText.create());
}