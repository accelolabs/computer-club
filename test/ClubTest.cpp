#include <gtest/gtest.h>
#include <variant>
#include <vector>

#include "src/event/Events.h"
#include "src/model/ComputerClub.h"
#include "src/model/HelperModels.h"
#include "src/model/Time.h"


TEST(ClubTestSuite, EarlyArrival) {
    ComputerClubConfig config {
        Time("11:11"),
        Time("22:22"),
        12,
        10
    };

    ComputerClub club(config);

    EventVariants event = club.handle_arrive({
        Time("01:44"),
        "Midnight Raccoon"
    });

    ASSERT_TRUE(std::get_if<ErrorEvent>(&event));
    ASSERT_STREQ(
        std::get_if<ErrorEvent>(&event) -> error_name.c_str(),
        "NotOpenYet"
    );
}


TEST(ClubTestSuite, AlreadyInClub) {
    ComputerClubConfig config {
        Time("11:11"),
        Time("22:22"),
        12,
        10
    };

    ComputerClub club(config);

    EventVariants event_1 = club.handle_arrive({
            Time("12:00"),
            "Double Trouble"
    });

    ASSERT_TRUE(std::get_if<EmptyEvent>(&event_1));

    EventVariants event_2 = club.handle_arrive({
        Time("13:00"),
        "Double Trouble"
    });

    ASSERT_TRUE(std::get_if<ErrorEvent>(&event_2));
    ASSERT_STREQ(
        std::get_if<ErrorEvent>(&event_2) -> error_name.c_str(),
        "YouShallNotPass"
    );
}


TEST(ClubTestSuite, SitUnknownClient) {
    ComputerClubConfig config {
        Time("11:11"),
        Time("22:22"),
        12,
        10
    };

    ComputerClub club(config);

    EventVariants event = club.handle_sit({
            Time("12:00"),
            "Who is that",
            1
    });

    ASSERT_TRUE(std::get_if<ErrorEvent>(&event));
    ASSERT_STREQ(
        std::get_if<ErrorEvent>(&event) -> error_name.c_str(),
        "ClientUnknown"
    );
}


TEST(ClubTestSuite, SitBusyPlace) {
    ComputerClubConfig config {
        Time("11:11"),
        Time("22:22"),
        12,
        10
    };

    ComputerClub club(config);

    club.handle_arrive({
            Time("12:00"),
            "productive gamer"
    });

    club.handle_sit({
        Time("13:00"),
        "productive gamer",
        1
    });

    EventVariants event = club.handle_sit({
        Time("14:00"),
        "productive gamer",
        1
    });

    ASSERT_TRUE(std::get_if<ErrorEvent>(&event));
    ASSERT_STREQ(
        std::get_if<ErrorEvent>(&event) -> error_name.c_str(),
        "PlaceIsBusy"
    );
}


TEST(ClubTestSuite, UnnecessaryWait) {
    ComputerClubConfig config {
        Time("11:11"),
        Time("22:22"),
        12,
        10
    };

    ComputerClub club(config);

    club.handle_arrive({
            Time("12:00"),
            "Slowpoke"
    });

    EventVariants event = club.handle_wait({
            Time("13:00"),
            "Slowpoke"
    });

    ASSERT_TRUE(std::get_if<ErrorEvent>(&event));
    ASSERT_STREQ(
        std::get_if<ErrorEvent>(&event) -> error_name.c_str(),
        "ICanWaitNoLonger!"
    );
}


TEST(ClubTestSuite, QueueTooLong) {
    ComputerClubConfig config {
        Time("11:11"),
        Time("22:22"),
        1,
        10
    };

    ComputerClub club(config);

    club.handle_arrive({
            Time("12:00"),
            "Linus"
    });

    // Linus gaming
    club.handle_sit({
            Time("12:05"),
            "Linus",
            1
    });

    club.handle_arrive({
            Time("12:10"),
            "Bjarne"
    });

    club.handle_arrive({
            Time("12:20"),
            "Terry"
    });

    EventVariants event = club.handle_wait({
            Time("13:00"),
            "Terry"
    });

    ASSERT_TRUE(std::get_if<ClientKickedEvent>(&event));
    ASSERT_STREQ(
        std::get_if<ClientKickedEvent>(&event) -> client_name.c_str(),
        "Terry"
    );
}


TEST(ClubTestSuite, LeaveFreesTable) {
    ComputerClubConfig config {
        Time("11:11"),
        Time("22:22"),
        1,
        10
    };

    ComputerClub club(config);

    club.handle_arrive({
            Time("12:00"),
            "Linus"
    });

    // Linus gaming
    club.handle_sit({
            Time("12:05"),
            "Linus",
            1
    });

    club.handle_arrive({
            Time("12:10"),
            "Bjarne"
    });

    EventVariants event = club.handle_leave({
            Time("12:15"),
            "Linus"
    });

    // Bjarne should be gaming
    ASSERT_TRUE(std::get_if<ClientDequeuedEvent>(&event));
    ASSERT_STREQ(
        std::get_if<ClientDequeuedEvent>(&event) -> client_name.c_str(),
        "Bjarne"
    );
}


TEST(ClubTestSuite, AlphabeticalKickAll) {
    ComputerClubConfig config {
        Time("11:11"),
        Time("22:22"),
        1,
        10
    };

    ComputerClub club(config);

    club.handle_arrive({
            Time("12:00"),
            "Linus"
    });

    club.handle_arrive({
            Time("12:10"),
            "Bjarne"
    });

    club.handle_arrive({
            Time("12:20"),
            "Terry"
    });

    std::vector<EventVariants> events = club.handle_close({
        Time("22:22")
    });

    ASSERT_EQ(events.size(), 3);
    EXPECT_STREQ(std::get<ClientKickedEvent>(events.at(0)).client_name.c_str(), "Bjarne");
    EXPECT_STREQ(std::get<ClientKickedEvent>(events.at(1)).client_name.c_str(), "Linus");
    EXPECT_STREQ(std::get<ClientKickedEvent>(events.at(2)).client_name.c_str(), "Terry");
}


TEST(ClubTestSuite, LogTables) {
    ComputerClubConfig config {
        Time("11:00"),
        Time("14:00"),
        4,
        10
    };

    ComputerClub club(config);

    club.handle_arrive({
            Time("11:50"),
            "Linus"
    });

    club.handle_arrive({
            Time("12:50"),
            "Bjarne"
    });

    club.handle_arrive({
            Time("12:20"),
            "Terry"
    });

    // Linus gaming
    club.handle_sit({
            Time("12:00"),
            "Linus",
            1
    });

    // Bjarne gaming
    club.handle_sit({
            Time("12:55"),
            "Bjarne",
            2
    });

    // Terry gaming
    club.handle_sit({
            Time("13:05"),
            "Terry",
            3
    });

    std::vector<EventVariants> kicks = club.handle_close({
        Time("14:00")
    });

    for (const auto& kick : kicks) {
        if (std::holds_alternative<ClientKickedEvent>(kick)) {
            club.handle_kick(std::get<ClientKickedEvent>(kick));
        }
    }

    std::vector<EventVariants> events = club.handle_tables_log();

    ASSERT_EQ(events.size(), 4);

    EXPECT_EQ(std::get<TableLogEvent>(events.at(0)).table_id, 1);
    EXPECT_STREQ(std::get<TableLogEvent>(events.at(0)).time.as_string().c_str(), "02:00");
    EXPECT_EQ(std::get<TableLogEvent>(events.at(0)).revenue, 20);

    EXPECT_EQ(std::get<TableLogEvent>(events.at(1)).table_id, 2);
    EXPECT_STREQ(std::get<TableLogEvent>(events.at(1)).time.as_string().c_str(), "01:05");
    EXPECT_EQ(std::get<TableLogEvent>(events.at(1)).revenue, 20);

    EXPECT_EQ(std::get<TableLogEvent>(events.at(2)).table_id, 3);
    EXPECT_STREQ(std::get<TableLogEvent>(events.at(2)).time.as_string().c_str(), "00:55");
    EXPECT_EQ(std::get<TableLogEvent>(events.at(2)).revenue, 10);

    EXPECT_EQ(std::get<TableLogEvent>(events.at(3)).table_id, 4);
    EXPECT_STREQ(std::get<TableLogEvent>(events.at(3)).time.as_string().c_str(), "00:00");
    EXPECT_EQ(std::get<TableLogEvent>(events.at(3)).revenue, 0);
}
