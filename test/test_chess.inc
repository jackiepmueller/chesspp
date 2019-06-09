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

TEST(boardFieldToOrdinal)
{
    TEST_ASSERT(boardFieldToOrdinal(1) == 0);
}
ENDTEST(boardFieldToOrdinal)

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

TEST(positionFromString)
{
    TEST_ASSERT(rankAndFileToBoardField(One,  A) == positionFromString("A1"));
    TEST_ASSERT(rankAndFileToBoardField(Five, H) == positionFromString("H5"));
}
ENDTEST(positionFromString)

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

    // Move the black rook out of the way
    gc.bR2.setPos(0);

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

    // first move by two
    auto & wP2 = gc.wP2;
    TEST_ASSERT(wP2.move(Four, B));
    TEST_ASSERT(wP2.pos() == rankAndFileToBoardField(Four, B));

    // second move not by two
    TEST_ASSERT(!wP2.move(Six, B));
    TEST_ASSERT(wP2.pos() == rankAndFileToBoardField(Four, B));
}
ENDTEST(pawnMovement)

TEST(pawnAttack)
{
    GameContext gc;

    auto & wP4 = gc.wP4;
    auto & bP6 = gc.bP6;

    TEST_ASSERT(wP4.move(Four, D));
    TEST_ASSERT(bP6.move(Five, C));

    TEST_ASSERT(wP4.move(Five, C));
    TEST_ASSERT(wP4.pos() == rankAndFileToBoardField(Five, C));
    TEST_ASSERT(!bP6.alive());
}
ENDTEST(pawnAttack)

TEST(side)
{
    GameContext gc;

    auto & wP1 = gc.wP1;
    auto & bP1 = gc.bP1;

    TEST_ASSERT(wP1.side() == Side::White);
    TEST_ASSERT(bP1.side() == Side::Black);
}
ENDTEST(side)

TEST(fileMask)
{
    GameContext gc;
    auto mask = fileMask(D);

    TEST_ASSERT(gc.wP4.pos() & mask);
    TEST_ASSERT(gc.wQ.pos() & mask);
    TEST_ASSERT(!(gc.wK.pos() & mask));
}
ENDTEST(fileMask)

TEST(rankMask)
{
    GameContext gc;
    auto mask = rankMask(Two);

    TEST_ASSERT(gc.wP1.pos() & mask);
    TEST_ASSERT(gc.wP4.pos() & mask);
    TEST_ASSERT(!(gc.wQ.pos() & mask));
    TEST_ASSERT(!(gc.wK.pos() & mask));
}
ENDTEST(rankMask)

TEST(sanParser)
{
    // Rook movement with ambiguity
    {
        GameContext gc;
        auto res = SANParser::parse(gc, "Ra4");
        TEST_ASSERT(res.reason == SANParser::Invalid);

        TEST_ASSERT(gc.wP1.move(Four, A));
        TEST_ASSERT(gc.wP8.move(Four, H));
        TEST_ASSERT(gc.wR1.move(Three, A));

        res = SANParser::parse(gc, "Rh3");
        TEST_ASSERT(res.reason == SANParser::Ambiguous);

        res = SANParser::parse(gc, "Rah3");
        TEST_ASSERT(res.reason == SANParser::Success);

        res = SANParser::parse(gc, "Rhh3");
        TEST_ASSERT(res.reason == SANParser::Success);

        res = SANParser::parse(gc, "R3h3");
        TEST_ASSERT(res.reason == SANParser::Success);

        res = SANParser::parse(gc, "Ra3h3");
        TEST_ASSERT(res.reason == SANParser::Success);

        // pawn in the way
        res = SANParser::parse(gc, "Rh1h4");
        TEST_ASSERT(res.reason == SANParser::Invalid);
    }

    // Pawn attack
    {
        GameContext gc;

        TEST_ASSERT(gc.wP4.move(Four, D));
        TEST_ASSERT(gc.bP4.move(Five, E));

        auto res = SANParser::parse(gc, "de5");
        TEST_ASSERT(res.reason == SANParser::Success);

        TEST_ASSERT(gc.gameState.move(res.from, res.to) == GameState::Success);
        TEST_ASSERT(gc.wP4.pos() == rankAndFileToBoardField(Five, E));
        TEST_ASSERT(!gc.bP4.alive());
    }
}
ENDTEST(sanParser)
