using namespace Chess;

TEST(rankAndFileToOrdinal)
{
    assert(rankAndFileToOrdinal(One,  A) == 0);
    assert(rankAndFileToOrdinal(One,  B) == 1);
    assert(rankAndFileToOrdinal(Five, E) == 36);
    assert(rankAndFileToOrdinal(Five, F) == 37);
    assert(rankAndFileToOrdinal(Six,  F) == 45);
}
ENDTEST(rankAndFileToOrdinal)

TEST(rankAndFileToBoardField)
{
    assert(rankAndFileToBoardField(One,  A) == 0b0000000000000000000000000000000000000000000001);
    assert(rankAndFileToBoardField(One,  B) == 0b0000000000000000000000000000000000000000000010);
    assert(rankAndFileToBoardField(Five, E) == 0b0000000001000000000000000000000000000000000000);
    assert(rankAndFileToBoardField(Five, F) == 0b0000000010000000000000000000000000000000000000);
    assert(rankAndFileToBoardField(Six,  F) == 0b1000000000000000000000000000000000000000000000);
}
ENDTEST(rankAndFileToBoardField)

TEST(toFromOrdinal)
{
    auto ordinal = rankAndFileToOrdinal(Six, F);
    auto bf = rankAndFileToBoardField(Six, F);

    assert(ordinal == boardFieldToOrdinal(bf));
}
ENDTEST(toFromOrdinal)

TEST(rankFromBoardField)
{
    {
        auto bf = rankAndFileToBoardField(Six, F);
        assert(rankFromBoardField(bf) == Six);
    }
    {
        auto bf = rankAndFileToBoardField(Three, A);
        assert(rankFromBoardField(bf) == Three);
    }
}
ENDTEST(rankFromBoardField)

TEST(fileFromBoardField)
{
    {
        auto bf = rankAndFileToBoardField(Six, F);
        assert(fileFromBoardField(bf) == F);
    }
    {
        auto bf = rankAndFileToBoardField(Three, A);
        assert(fileFromBoardField(bf) == A);
    }
}
ENDTEST(fileFromBoardField)

TEST(pawnMovement)
{
    GameContext gc;

    auto & wP1 = gc.wP1;

    assert(wP1.move(Three, A));
    assert(wP1.pos() == rankAndFileToBoardField(Three, A));

    assert(!wP1.move(Three, A));
    assert(wP1.pos() == rankAndFileToBoardField(Three, A));

    assert(wP1.move(Four, A));
    assert(wP1.pos() == rankAndFileToBoardField(Four, A));

    assert(wP1.move(Five, A));
    assert(wP1.pos() == rankAndFileToBoardField(Five, A));

    assert(wP1.move(Six, A));
    assert(wP1.pos() == rankAndFileToBoardField(Six, A));

    assert(!wP1.move(Seven, A));
    assert(wP1.pos() == rankAndFileToBoardField(Six, A));

    // Move the opposing black pawn out of the way
    gc.bP8.setPos(0);

    assert(wP1.move(Seven, A));
    assert(wP1.pos() == rankAndFileToBoardField(Seven, A));

    assert(wP1.move(Eight, A));
    assert(wP1.pos() == rankAndFileToBoardField(Eight, A));

    // Can't go past end of board
    assert(!wP1.move(Eight + 1, A));
    assert(wP1.pos() == rankAndFileToBoardField(Eight, A));

    assert(!wP1.move(One, A));
    assert(wP1.pos() == rankAndFileToBoardField(Eight, A));

    // Can't go backwards
    assert(!wP1.move(Seven, A));
    assert(wP1.pos() == rankAndFileToBoardField(Eight, A));
}
ENDTEST(pawnMovement)
