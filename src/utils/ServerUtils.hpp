#pragma once
#include <Geode/Geode.hpp>
#include <Geode/utils/web.hpp>

class ServerUtils {
public:
    static geode::utils::web::WebRequest getBaseRequest();
    static std::string getBaseURL();
    static std::string getBasePostString();
    static std::vector<std::string> split(const std::string&, char);
    static void getOnlineLevels(GJSearchObject* searchObject, std::function<void(std::shared_ptr<std::vector<geode::Ref<GJGameLevel>>>)> callback);
};
