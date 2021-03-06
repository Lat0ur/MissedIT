#pragma GCC diagnostic ignored "-Wwrite-strings"
#pragma GCC diagnostic ignored "-Wformat-security"

#include "antiaimtab.h"

#include "../../interfaces.h"
#include "../../Utils/xorstring.h"
#include "../../settings.h"
#include "../../Hacks/valvedscheck.h"
#include "../../ImGUI/imgui_internal.h"
#include "../atgui.h"



static void RageAntiAIm()
{
    const char* yType[] = {
        "NONE",
        "Static",
        "Jitter",
        "Random",
    };

    const char* RageAntiAimType[] = {
        "Default Rage",
        "Fake Arround Real",
	    "Real Arround Fake",
        "Semi Direction",
        "Free Stand",
    };
    ImGui::Columns(1, nullptr, false); // Pick Rage Anti Aim type
    {
        ImGui::PushItemWidth(-1);
        ImGui::Combo(XORSTR("##RageAntiAimType"), (int*)&Settings::AntiAim::RageAntiAim::Type, RageAntiAimType, IM_ARRAYSIZE(RageAntiAimType));
        ImGui::PopItemWidth();
    }

    if (Settings::AntiAim::RageAntiAim::Type == RageAntiAimType::FreeStand)
    {
        ImGui::Columns(2, nullptr, false);
        {
            ImGui::ItemSize(ImVec2(0.0f, 0.0f), 0.0f);
            ImGui::Text(XORSTR("Yaw Actual"));
        }
        ImGui::NextColumn();
        {
            ImGui::PushItemWidth(-1);
            ImGui::Combo(XORSTR("##YACTUALTYPE"), (int*)& Settings::AntiAim::Yaw::typeReal, yType, IM_ARRAYSIZE(yType));
            ImGui::PopItemWidth();
        }

        if(Settings::AntiAim::Yaw::typeReal == AntiAimRealType_Y::Jitter)
            ImGui::SliderFloat(XORSTR("##RealJitterPercentage"), &Settings::AntiAim::RageAntiAim::JitterPercent, 1, 100, "Real Jitter Ammount : %.0f perent");
    }
    else
    {
        ImGui::Columns(2, nullptr, false);
        {
            ImGui::ItemSize(ImVec2(0.0f, 0.0f), 0.0f);
            ImGui::Text(XORSTR("Yaw Fake"));
            ImGui::ItemSize(ImVec2(0.0f, 0.0f), 0.0f);
            ImGui::Text(XORSTR("Yaw Actual"));
        }
        ImGui::NextColumn();
        {
            ImGui::PushItemWidth(-1);
            ImGui::Combo(XORSTR("##YFAKETYPE"), (int*)&Settings::AntiAim::Yaw::typeFake, yType, IM_ARRAYSIZE(yType));
            ImGui::Combo(XORSTR("##YACTUALTYPE"), (int*)& Settings::AntiAim::Yaw::typeReal, yType, IM_ARRAYSIZE(yType));
            ImGui::PopItemWidth();
        }
        // Real Percentage
        ImGui::Columns(1);
        {
            ImGui::PushItemWidth(-1);
            ImGui::SliderFloat(XORSTR("##MaxDeltaPercentage"), &Settings::AntiAim::RageAntiAim::AntiAImPercent, 0, 100, "Max Delta Ammount : %.0f percent");

            if(Settings::AntiAim::Yaw::typeReal == AntiAimRealType_Y::Jitter || Settings::AntiAim::Yaw::typeFake == AntiAimFakeType_y::Jitter)
                ImGui::SliderFloat(XORSTR("##JitterPercentage"), &Settings::AntiAim::RageAntiAim::JitterPercent, 0, 100, "Jitter Ammount : %.0f perent"); 
         
            ImGui::PopItemWidth();
        }
    }

    ImGui::Spacing(); ImGui::Spacing();
    ImGui::Columns(1, nullptr, false);
    
    ImGui::Checkbox(XORSTR("At the Target(alfa)"), &Settings::AntiAim::RageAntiAim::atTheTarget);
    

    ImGui::Spacing(); ImGui::Spacing();
    ImGui::Columns(1);
    ImGui::Text(XORSTR("Edging(Alfa)"));
    
    ImGui::Columns(2, nullptr, false);
    {
        ImGui::Checkbox(XORSTR("Enabled"), &Settings::AntiAim::HeadEdge::enabled);
    }
    ImGui::NextColumn();
    {
        ImGui::PushItemWidth(-1);
        ImGui::SliderFloat(XORSTR("##EDGEDISTANCE"), &Settings::AntiAim::HeadEdge::distance, 20, 30, "Distance: %0.0f");
        ImGui::PopItemWidth();
    }

    /*
    ** Starting of Manual anti aim
    */
    ImGui::Spacing(); ImGui::Spacing();
    ImGui::Columns(1);
    ImGui::Checkbox(XORSTR("##Manual Anti Aim"), &Settings::AntiAim::ManualAntiAim::Enable);
    ImGui::SameLine();
    ImGui::Text(XORSTR("Manuan AntiAim"));

    //For player to move right
    ImGui::Text("Align Right");
    ImGui::SameLine();
    ImGui::PushItemWidth(-1);
    UI::KeyBindButton(&Settings::AntiAim::ManualAntiAim::RightButton);
    ImGui::PopItemWidth();

    // For player Move back
    ImGui::Text("Align Back");
    ImGui::SameLine();
    ImGui::PushItemWidth(-1);
    UI::KeyBindButton(&Settings::AntiAim::ManualAntiAim::backButton);
    ImGui::PopItemWidth();

    //For player to move left
    ImGui::Text("Align Left");
    ImGui::SameLine();
    ImGui::PushItemWidth(-1);
    UI::KeyBindButton(&Settings::AntiAim::ManualAntiAim::LeftButton);
    ImGui::PopItemWidth();
    // END
}

static void LegitAntiAim()
{
    const char* LegitAAType[] = {
                                "OverWatchProof",
                                "FakeLegitAA",
                                "Experimental"
                                };
    /*
    * part where legit anti aim ui constructed
    */
    // Really nothing much here to add more about
    ImGui::Spacing();
    ImGui::PushItemWidth(-1);
    ImGui::Combo(XORSTR("##LegitAAType"), (int*)&Settings::AntiAim::LegitAntiAim::legitAAtype, LegitAAType, IM_ARRAYSIZE(LegitAAType));
    ImGui::Spacing();
    ImGui::Columns(1, nullptr, false);
    ImGui::Text(XORSTR("InvertKey"));
    ImGui::SameLine();
    UI::KeyBindButton(&Settings::AntiAim::LegitAntiAim::InvertKey); 
    ImGui::PopItemWidth();
    /*
    * End of legit antiaim
    */
}

static void LagacyAntiAim()
{
    ImGui::SliderFloat(XORSTR("##LBYOFFSET"), &Settings::AntiAim::LBYBreaker::offset, 0, 360, "LBY Offset(from fake): %0.f");
}
void HvH::RenderTab()
{
    
    static char* AntiAimType[] = {
        "Legit AntiAIm",
        "Rage AntiAIm",
        "LBY Breaker",
    }; 
    
    ImGui::Spacing();

    ImGui::Columns(2, nullptr, false);
    {
        switch (Settings::AntiAim::Type::antiaimType)
        {
        case AntiAimType::LegitAntiAim:
           if ( ImGui::Checkbox(XORSTR("##EnableLegitAim"), &Settings::AntiAim::LegitAntiAim::enable) )
                Settings::AntiAim::RageAntiAim::enable = false;
            break;
        case AntiAimType::RageAntiAim:
            if ( ImGui::Checkbox(XORSTR("##EnableRageAntiAim"), &Settings::AntiAim::RageAntiAim::enable) )
                Settings::AntiAim::LegitAntiAim::enable = false;
            break;
        case AntiAimType::Lagacy:
            ImGui::Checkbox(XORSTR("##ENABLELbyBreaker"), &Settings::AntiAim::LBYBreaker::enabled);
            break;
        default:
            break;
        }
            
        ImGui::SameLine();
        ImGui::PushItemWidth(-1);
        ImGui::Combo(XORSTR("##AntiAimType"), (int*)&Settings::AntiAim::Type::antiaimType, AntiAimType, IM_ARRAYSIZE(AntiAimType));
        ImGui::PopItemWidth();
        ImGui::BeginChild(XORSTR("HVH1"), ImVec2(0, 0), false);
        {
            switch (Settings::AntiAim::Type::antiaimType)
            {
            case AntiAimType::RageAntiAim:
                RageAntiAIm();
                break;
            case AntiAimType::LegitAntiAim:
                LegitAntiAim();
                break;
            case AntiAimType::Lagacy:
                LagacyAntiAim();
                break;
            default:
                break;
            }
        }
        ImGui::EndChild();
    }
    ImGui::NextColumn();
    {
        ImGui::BeginChild(XORSTR("HVH2"), ImVec2(0, 0), false);
        {
            ImGui::Checkbox(XORSTR("Angle Indicator"), &Settings::AngleIndicator::enabled);
            ImGui::Checkbox(XORSTR("Fake Lag"), &Settings::FakeLag::enabled);
            ImGui::SameLine();
            ImGui::SliderInt(XORSTR("##FAKELAGAMOUNT"), &Settings::FakeLag::value, 0, 100, XORSTR("Amount: %0.f"));
			ImGui::Checkbox(XORSTR("Adaptive Fake Lag"), &Settings::FakeLag::adaptive);
            
            ImGui::Checkbox(XORSTR("FakeDuck"), &Settings::AntiAim::FakeDuck::enabled);
            ImGui::SameLine(); 
            UI::KeyBindButton(&Settings::AntiAim::FakeDuck::fakeDuckKey);
            ImGui::EndChild();
        }
    }
}
