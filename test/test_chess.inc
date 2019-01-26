// vi:syntax=cpp

using namespace Chess;

TEST(rankAndFileToOrdinal)
{
    TEST_ASSERT(rankAndFileToOrdinal(One,  A) == 0);
    TEST_ASSERT(rankAndFileToOrdinal(One,  B) == 1);
    TEST_ASSERT(rankAndFileToOrdinal(Five, E) == 36);
    TEST_ASSERT(rankAndFileToOrdinal(Five, F) == 37);
    TEST_ASSERT(rankAndFileToOrdinal(Six,  F) == 45);
}
ENDTEST(rankAndFileToOrdinal)

TEST(rankAndFileToBoardField)
{
    TEST_ASSERT(rankAndFileToBoardField(One,  A) == 0b0000000000000000000000000000000000000000000001);
    TEST_ASSERT(rankAndFileToBoardField(One,  B) == 0b0000000000000000000000000000000000000000000010);
    TEST_ASSERT(rankAndFileToBoardField(Five, E) == 0b0000000001000000000000000000000000000000000000);
    TEST_ASSERT(rankAndFileToBoardField(Five, F) == 0b0000000010000000000000000000000000000000000000);
    TEST_ASSERT(rankAndFileToBoardField(Six,  F) == 0b1000000000000000000000000000000000000000000000);
}
ENDTEST(rankAndFileToBoardField)

TEST(toFromOrdinal)
{
    auto ordinal = rankAndFileToOrdinal(Six, F);
    auto bf = rankAndFileToBoardField(Six, F);

    TEST_ASSERT(ordinal == boardFieldToOrdinal(bf));
}
ENDTEST(toFromOrdinal)

TEST(rankFromBoardField)
{
    {
        auto bf = rankAndFileToBoardField(Six, F);
        TEST_ASSERT(rankFromBoardField(bf) == Six);
    }
    {
        auto bf = rankAndFileToBoardField(Three, A);
        TEST_ASSERT(rankFromBoardField(bf) == Three);
    }
}
ENDTEST(rankFromBoardField)

TEST(fileFromBoardField)
{
    {
        auto bf = rankAndFileToBoardField(Six, F);
        TEST_ASSERT(fileFromBoardField(bf) == F);
    }
    {
        auto bf = rankAndFileToBoardField(Three, A);
        TEST_ASSERT(fileFromBoardField(bf) == A);
    }
}
ENDTEST(fileFromBoardField)

TEST(pawnMovement)
{
    GameContext gc;

    auto & wP1 = gc.wP1;

    TEST_ASSERT(wP1.move(Three, A));
    TEST_ASSERT(wP1.pos() == rankAndFileToBoardField(Three, A));

    TEST_ASSERT(!wP1.move(Three, A));
    TEST_ASSERT(wP1.pos() == rankAndFileToBoardField(Three, A));

    TEST_ASSERT(wP1.move(Four, A));
    TEST_ASSERT(wP1.pos() == rankAndFileToBoardField(Four, A));

    TEST_ASSERT(wP1.move(Five, A));
    TEST_ASSERT(wP1.pos() == rankAndFileToBoardField(Five, A));

    TEST_ASSERT(wP1.move(Six, A));
    TEST_ASSERT(wP1.pos() == rankAndFileToBoardField(Six, A));

    TEST_ASSERT(!wP1.move(Seven, A));
    TEST_ASSERT(wP1.pos() == rankAndFileToBoardField(Six, A));

    // Move the opposing black pawn out of the way
    gc.bP8.setPos(0);

    TEST_ASSERT(wP1.move(Seven, A));
    TEST_ASSERT(wP1.pos() == rankAndFileToBoardField(Seven, A));

    TEST_ASSERT(wP1.move(Eight, A));
    TEST_ASSERT(wP1.pos() == rankAndFileToBoardField(Eight, A));

    // Can't go past end of board
    TEST_ASSERT(!wP1.move(Eight + 1, A));
    TEST_ASSERT(wP1.pos() == rankAndFileToBoardField(Eight, A));

    TEST_ASSERT(!wP1.move(One, A));
    TEST_ASSERT(wP1.pos() == rankAndFileToBoardField(Eight, A));

    // Can't go backwards
    TEST_ASSERT(!wP1.move(Seven, A));
    TEST_ASSERT(wP1.pos() == rankAndFileToBoardField(Eight, A));
}
ENDTEST(pawnMovement)

TEST(side)
{
    GameContext gc;

    auto & wP1 = gc.wP1;
    auto & bP1 = gc.bP1;

    TEST_ASSERT(wP1.side() == Side::White);
    TEST_ASSERT(bP1.side() == Side::Black);
}
ENDTEST(side)
