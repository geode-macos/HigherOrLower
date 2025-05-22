#include "ServerUtils.hpp"
#include "../utils.hpp"

//Stolen from Cvolton <3
using namespace geode::prelude;

web::WebRequest ServerUtils::getBaseRequest() {
    return web::WebRequest();
}

std::string ServerUtils::getBaseURL() {
    return "https://www.boomlings.com/database";
}

std::string ServerUtils::getBasePostString() {
    return fmt::format("gameVersion={}&binaryVersion={}", 22, 42);
}

void ServerUtils::getOnlineLevels(GJSearchObject* searchObject, std::function<void(std::shared_ptr<std::vector<Ref<GJGameLevel>>>)> callback) {
    std::string postString = fmt::format(
        "{}&type={}&str={}&page={}&secret=Wmfd2893gb7",
        getBasePostString(),
        static_cast<int>(searchObject->m_searchType),
        searchObject->m_searchQuery,
        searchObject->m_page
    );
    postString += GameLevelManager::sharedState()->writeSpecialFilters(searchObject);

    getBaseRequest()
        .bodyString(postString)
        .post(fmt::format("{}/getGJLevels21.php", getBaseURL()))
        .listen([callback](web::WebResponse* response) {
        auto levels = std::make_shared<std::vector<Ref<GJGameLevel>>>();

        if (!response->ok() || response->string().unwrapOr("") == "-1") {
            callback(levels);
            return *response;
        }

        std::string str = response->string().unwrapOr("");

        std::stringstream stream(str);
        std::string levelData;
        std::string userData;

        getline(stream, levelData, '#');
        getline(stream, userData, '#');
        
        std::stringstream userStream(userData);
        std::string currentUser;
        while (getline(userStream, currentUser, '|')) {
            auto info = utils::string::split(currentUser, ":");
            if (info.size() < 3) continue;

            int userID = 0;
            std::from_chars(info[0].data(), info[0].data() + info[0].size(), userID);
            int accountID = 0;
            std::from_chars(info[2].data(), info[2].data() + info[2].size(), accountID);

            if (userID > 0) GameLevelManager::sharedState()->storeUserName(userID, accountID, info[1]);
        }

        std::stringstream levelStream(levelData);
        std::string currentLevel;
        while (getline(levelStream, currentLevel, '|')) {
            auto level = GJGameLevel::create(GameLevelManager::responseToDict(currentLevel, false), false);
            levels->push_back(level);
        }

        callback(levels);
        return *response;
            });
}

std::vector<std::string> ServerUtils::split(const std::string& str, char delimiter) {
    std::vector<std::string> parts;
    std::stringstream ss(str);
    std::string item;
    while (std::getline(ss, item, delimiter)) {
        parts.push_back(item);
    }
    return parts;
}