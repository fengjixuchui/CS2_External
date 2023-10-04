#include "ConfigMenu.hpp"
#include "../MenuConfig.hpp"
#include "ConfigSaver.hpp"
#include "../TriggerBot.h"
#include "../AimBot.hpp"
#include <filesystem>

namespace ConfigMenu {

    void RenderConfigMenu() {
		// Config
		if (ImGui::CollapsingHeader("Config "))
		{
			static char configNameBuffer[128] = "";

			ImGui::InputText("New Config Name", configNameBuffer, sizeof(configNameBuffer));

			if (ImGui::Button("Create Config"))
			{
				std::string configFileName = std::string(configNameBuffer) + ".config";
				MyConfigSaver::SaveConfig(configFileName);
			}

			ImGui::Separator();

			static int selectedConfig = -1;

			const std::string configDir = std::filesystem::current_path().string();
			static std::vector<std::string> configFiles;

			configFiles.clear();
			for (const auto& entry : std::filesystem::directory_iterator(configDir))
			{
				if (entry.is_regular_file() && entry.path().extension() == ".config")
				{
					configFiles.push_back(entry.path().filename().string());
				}
			}

			for (int i = 0; i < configFiles.size(); ++i)
			{
				if (ImGui::Selectable(configFiles[i].c_str(), selectedConfig == i))
				{
					selectedConfig = i;
				}
			}

			if (selectedConfig != -1)
			{
				ImGui::Text("Selected Config: %s", configFiles[selectedConfig].c_str());
			}

			if (ImGui::Button("Load Selected") && selectedConfig >= 0 && selectedConfig < configFiles.size())
			{
				std::string selectedConfigFile = configFiles[selectedConfig];
				MyConfigSaver::LoadConfig(selectedConfigFile);
			}

			if (ImGui::Button("Save Selected") && selectedConfig >= 0 && selectedConfig < configFiles.size())
			{
				std::string selectedConfigFile = configFiles[selectedConfig];
				MyConfigSaver::SaveConfig(selectedConfigFile);
			}

			ImGui::Separator();

			if (ImGui::Button("Delete Selected") && selectedConfig >= 0 && selectedConfig < configFiles.size())
			{
				std::string selectedConfigFile = configFiles[selectedConfig];
				std::string fullPath = configDir + "/" + selectedConfigFile;
				if (std::remove(fullPath.c_str()) == 0)
				{
					configFiles.erase(configFiles.begin() + selectedConfig);
					selectedConfig = -1;
				}
				else
				{
				}
			}

			if (ImGui::Button("Reset to Default"))
			{
				ConfigMenu::ResetToDefault();
			}
		}
    }

    void ResetToDefault() {
		MenuConfig::ShowBoneESP = true;
		MenuConfig::ShowBoxESP = true;
		MenuConfig::ShowHealthBar = true;
		MenuConfig::ShowWeaponESP = true;
		MenuConfig::ShowEyeRay = true;
		MenuConfig::ShowPlayerName = true;

		MenuConfig::AimBot = true;
		MenuConfig::AimPosition = 0;
		MenuConfig::AimPositionIndex = BONEINDEX::head;
		MenuConfig::BoxType = 0;
		MenuConfig::HealthBarType = 0;
		MenuConfig::BoneColor = ImVec4(255, 255, 255, 255);
		MenuConfig::BoxColor = ImVec4(255, 255, 255, 255);
		MenuConfig::EyeRayColor = ImVec4(255, 0, 0, 255);
		MenuConfig::ShowMenu = true;
		MenuConfig::ShowRadar = true;
		MenuConfig::RadarRange = 150;
		MenuConfig::ShowRadarCrossLine = true;
		MenuConfig::RadarCrossLineColor = ImVec4(34, 34, 34, 180);
		MenuConfig::RadarType = 2;
		MenuConfig::Proportion = 2300;
		MenuConfig::TriggerBot = true;
		MenuConfig::TeamCheck = true;
		MenuConfig::ShowHeadShootLine = true;
		MenuConfig::HeadShootLineColor = ImVec4(255, 255, 255, 255);
		MenuConfig::AimBotHotKey = 0;
		MenuConfig::ShowLineToEnemy = true;
		MenuConfig::FovLineSize = 60.0f;
		TriggerBot::TriggerDelay = 90;
		AimControl::RCSBullet = 1;
		TriggerBot::HotKey = VK_LMENU;
		MenuConfig::ShowLineToEnemy = true;
		AimControl::RCSScale = ImVec2(1.2f, 1.4f);
		MenuConfig::FovLineColor = ImVec4(55, 55, 55, 220);
		MenuConfig::LineToEnemyColor = ImVec4(255, 255, 255, 220);
    }
}