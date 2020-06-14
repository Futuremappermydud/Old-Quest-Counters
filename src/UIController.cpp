#include "../include/Main.hpp"

Il2CppObject* PlayButton;

Il2CppObject* SwitchButton;
Il2CppObject* SwitchButtonTMP;

Il2CppObject* ToggleButton;
Il2CppObject* ToggleButtonTMP;

enum UI 
{
	Hit,
	Miss,
	Bomb,
	Accuracy,
	PB,
	SaberSpeed,
	WallsLeft,
	NotesLeft,
	PlayCount,
} UIType;

int index = 0;

void SetConfigValue(UI Type, bool Value)
{
	switch (Type)
	{
	case Hit:
		getConfig().config["Hit Notes Counter"].SetBool(Value);
		break;
	case Miss:
		getConfig().config["Missed Notes Counter"].SetBool(Value);
		break;
	case Bomb:
		getConfig().config["Hit Bomb Counter"].SetBool(Value);
		break;
	case Accuracy:
		getConfig().config["Accuracy Counter"].SetBool(Value);
		break;
	case PB:
		getConfig().config["Personal Best Counter"].SetBool(Value);
		break;
	case SaberSpeed:
		getConfig().config["Saber Speed Counter"].SetBool(Value);
		break;
	case WallsLeft:
		getConfig().config["Walls Left / Wall Percentage"].SetBool(Value);
		break;
	case NotesLeft:
		getConfig().config["Notes Left / Note Percentage"].SetBool(Value);
		break;
		case PlayCount:
		getConfig().config["Play Count(er)"].SetBool(Value);
		break;
	default:
		break;
	}
}

bool GetConfigValue(UI Type)
{
	LoadConfig();
	switch (Type)
	{
	case Hit:
		return getConfig().config["Hit Notes Counter"].GetBool();
		break;
	case Miss:
		return getConfig().config["Missed Notes Counter"].GetBool();
		break;
	case Bomb:
		return getConfig().config["Hit Bomb Counter"].GetBool();
		break;
	case Accuracy:
		return getConfig().config["Accuracy Counter"].GetBool();
		break;
	case PB:
		return getConfig().config["Personal Best Counter"].GetBool();
		break;
	case SaberSpeed:
		return getConfig().config["Saber Speed Counter"].GetBool();
		break;
	case WallsLeft:
		return getConfig().config["Walls Left / Wall Percentage"].GetBool();
		break;
	case NotesLeft:
		return getConfig().config["Notes Left / Note Percentage"].GetBool();
		break;
		case PlayCount:
		return getConfig().config["Play Count(er)"].GetBool();
		break;
	default:
		break;
	}
	
}

std::string GetText(UI Type)
{
	switch (Type)
	{
	case Hit:
		return "Hits";
		break;
	case Miss:
		return "Misses";
		break;
	case Bomb:
		return "Bombs";
		break;
	case Accuracy:
		return "Accuracy";
		break;
	case PB:
		return "PB";
		break;
	case SaberSpeed:
		return "Speed";
		break;
	case WallsLeft:
		return "Walls Left";
		break;
	case NotesLeft:
		return "Notes Left";
		break;
		case PlayCount:
		return "Play Count";
		break;
	default:
		return "Unknow poggers";
		break;
	}
}

std::string GetEnabledText(UI Type)
{
	return GetConfigValue(Type) ? "Enabled" : "Disabled";
}

void SwitchCounter()
{
	index++;
	if(index == 9) index = 0;
	UIType = (UI)index;
	std::string Text = GetText(UI(index));
    RunMethod(SwitchButtonTMP, "set_text", createcsstr(Text));
	RunMethod(ToggleButtonTMP, "set_text", createcsstr(GetEnabledText(UI(index))));
}

void Toggle()
{
	SetConfigValue(UI(index) , ! GetConfigValue(UI(index)));
	RunMethod(ToggleButtonTMP, "set_text", createcsstr(GetEnabledText(UI(index))));
}

void Destroy(Il2CppObject* obj)
{
    RunMethod("UnityEngine", "Object", "Destroy", obj);
}

void SettingsUI_Start(Il2CppObject* self)
{
	//Switch
	Vector3 Pos = {0, 0, 2.0f};
    Vector3 Scale = {1, 1, 1};
	PlayButton = *GetFieldValue(self, "_continueButton");	
	index = 0;
	SwitchButton = *RunMethod("UnityEngine", "Object", "Instantiate", PlayButton);
    auto PlayButtonTransform = CRASH_UNLESS(il2cpp_utils::RunMethod(PlayButton, "get_transform"));
    auto parent = CRASH_UNLESS(il2cpp_utils::RunMethod(PlayButtonTransform, "get_parent"));
    Il2CppObject* OnClick = CRASH_UNLESS(il2cpp_utils::GetPropertyValue(SwitchButton, "onClick"));
	std::string SwitchButtonText = GetText(UI(index));
	auto SwitchButtonTransform = CRASH_UNLESS(il2cpp_utils::RunMethod(SwitchButton, "get_transform"));
	RunMethod(SwitchButtonTransform, "SetParent", parent);
	RunMethod(SwitchButtonTransform, "set_position", Pos);
    RunMethod(SwitchButtonTransform, "set_localScale", Scale);
    Il2CppObject* SwitchButtonObj2 = *RunMethod(SwitchButton, "get_gameObject");
    SwitchButtonTMP = *RunMethod(SwitchButtonObj2, "GetComponentInChildren", GetSystemType("TMPro", "TextMeshProUGUI"));
    auto SwitchButtonTMPLocalizer = *RunMethod(SwitchButtonObj2, "GetComponentInChildren", GetSystemType("Polyglot", "LocalizedTextMeshProUGUI"));
    if (SwitchButtonTMPLocalizer != nullptr)
    {
        Destroy(SwitchButtonTMPLocalizer);
    }
    RunMethod(SwitchButtonTMP, "set_text", createcsstr(SwitchButtonText));
    auto action = MakeAction(il2cpp_functions::class_get_type(il2cpp_utils::GetClassFromName("UnityEngine.Events", "UnityAction")), (Il2CppObject*)nullptr, SwitchCounter);
    RunMethod(OnClick, "AddListener", action);
	
	//Toggle

	ToggleButton = *RunMethod("UnityEngine", "Object", "Instantiate", PlayButton);
    Il2CppObject* OnClick2 = CRASH_UNLESS(il2cpp_utils::GetPropertyValue(ToggleButton, "onClick"));
	std::string ToggleButtonText = GetText(UI(index));
	auto ToggleButtonTransform = CRASH_UNLESS(il2cpp_utils::RunMethod(ToggleButton, "get_transform"));
	RunMethod(ToggleButtonTransform, "SetParent", parent);
	RunMethod(ToggleButtonTransform, "set_position", Pos);
    RunMethod(ToggleButtonTransform, "set_localScale", Scale);
    Il2CppObject* ToggleButtonObj2 = *RunMethod(ToggleButton, "get_gameObject");
    ToggleButtonTMP = *RunMethod(ToggleButtonObj2, "GetComponentInChildren", GetSystemType("TMPro", "TextMeshProUGUI"));
    auto ToggleButtonTMPLocalizer = *RunMethod(ToggleButtonObj2, "GetComponentInChildren", GetSystemType("Polyglot", "LocalizedTextMeshProUGUI"));
    if (ToggleButtonTMPLocalizer != nullptr)
    {
        Destroy(ToggleButtonTMPLocalizer);
    }
    RunMethod(ToggleButtonTMP, "set_text", createcsstr(GetEnabledText(UI(index))));
    auto action2 = MakeAction(il2cpp_functions::class_get_type(il2cpp_utils::GetClassFromName("UnityEngine.Events", "UnityAction")), (Il2CppObject*)nullptr, Toggle);
    RunMethod(OnClick2, "AddListener", action2);
}