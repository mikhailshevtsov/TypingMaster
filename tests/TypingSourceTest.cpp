#include <gtest/gtest.h>

#include <QTextStream>
#include <QFile>

#include "TypingSource.hpp"

class TypingSourceTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        buffer = R"(
            A sceptic is a person who, when he sees the handwriting on the wall and claims it's a forgery.
            A successful marriage isn't finding the right person, it's being the right person.
            Feed your faith and your doubts will starve to death.
            God gave the angels Wings, and He gave humans Chocolate!
            God wants spiritual fruit, NOT religious nuts.
            If God had meant us to look back instead of forward, he would have put eyes in the back of our head.
            If the grass is greener on the other side of the fence, you can bet the water bill is much higher.
            It isn't difficult to make a mountain out of a molehill - just add a little more dirt.
            It's all right to sit on your pity pot every now and again.
            Just be sure to flush when you are done.
            Kind and loving words are windows to the heart.
            Many marriages are made in heaven, but they ALL have to be maintained on earth.
            People who feel they need control lack self-control.
            Some folks wear their halos much too tight which cuts off circulation to the brain.
            Sorrow looks back, worry looks around, and faith looks UP.
            Standing in the middle of the road is dangerous, you will get knocked down by the traffic from both directions.
            The best way to get even is to forgive and then forget!
            The mighty oak tree was once a little nut that held its ground.
            The tongue must be heavy indeed, so few people can hold it.
            To forgive is to set the prisoner free, and then discover all along the prisoner was you!
            Too many people offer God prayers, with claw marks all over them.
            Unless you can create the whole universe in 5 days, then perhaps giving advice to God, isn't such a good idea!
            You have to wonder about humans, they think God is dead and Elvis is still alive!
            You'll notice that a turtle only makes progress when it sticks out its neck.
            It doesn't matter if you're on the right track, if you don't move, you'll get run over.
            Men do not like to admit to even momentary imperfection.
            My husband forgot the code to turn off the alarm.
            When the police came, he wouldn't admit he'd forgotten the code.
            Some people say that I must be a horrible person, but that's not true.
            I have the heart of a young boy - in a jar on my desk.
            If you water it and it dies, it's a plant.
            If you pull it out and it grows back, it's a weed.
            Clothes make the man.
            Naked people have little or no influence on society.
            The only winner in the War of 1812 was Tchaikovsky.
            Blessed are we who can laugh at ourselves for we shall never cease to be amused.
            Learn from the past.
            Look to the future.
            Live in the present.
            Life is ours to be spent, not saved.
            What makes old age so sad is not that our joys but our hopes cease.
            If you wish you be like someone else, you waste the person you are.
            Nothing can bring you peace but yourself.
            If I could drop dead right now, I'd be the happiest man alive.
            The surest way of severely upsetting yourself for hours is by continuing to consider what concerns you most for a single moment too long.
            Anxiety is interest paid on trouble before it is due.
            Even the the most tempting rose has thorns.
            I look forward to an America which will not be afraid of grace and beauty.
            A home is not a mere transient shelter: its essence lies in the personalities of the people who live in it.
            A lifetime of happiness!
            No man alive could bear it; it would be hell on earth.
            Poverty doesn't bring unhappiness; it brings degradation.
            Be good and you will be lonesome.
            I advise you to go on living solely to enrage those who are paying your annuities.
            It is the only pleasure I have left.
            In life, we are all in the gutter.
            Some of us just tend to look up at the stars.
            All who would win joy, must share it; happiness was born a twin.
            Don't underestimate the value of doing nothing, of just going along, listening to all the things you can't hear, and not bothering.
            When the world has once begun to use us ill, it afterwards continues the same treatment with less scruple or ceremony, as men do to a whore.
            For those who fight for it, life has a flavour the sheltered will never know.
            Live each day as if it were the last day of your life, because so far, it is.
            To live a perfect life, you must ask nothing, give nothing, and expect nothing.
            Expect everything, and anything seems nothing.
            Expect nothing, and anything seems everything.
            A man can do what he wants, but not want what he wants.
            If we couldn't laugh, we'd all go insane.
            If life doesn't offer a game worth playing, then invent a new one.
            There is more to life than increasing its speed.
            Freedom is the freedom to say that two plus two equals four.
            If that is granted, all else follows.
            Anxiety is a thin stream of fear trickling through the mind.
            If encouraged, it cuts a channel into which all other thoughts are drained.
            There is no excellent beauty that hath not some strangeness in the proportion.
            Comedy is tragedy plus time.
            Though we travel the world over to find the beautiful, we must carry it with us or we find it not.
            He is happiest who hath power to gather wisdom from a flower.
            Do not scorn the person who is perpetually happy.
            He does know something you don't.
            Joy is not in things, it is in us.
        )";
        buffer = buffer.simplified();

        file.setFileName(fileName);
        file.open(QFile::Text | QFile::WriteOnly);
        QTextStream(&file) << buffer;
        file.close();
    }

    void TearDown() override
    {
        file.remove();
    }

    TypingSource ts;
    QFile file;
    QString buffer;
    QString fileName = "test.txt";
};

TEST_F(TypingSourceTest, EmptyBufferTest)
{
    ASSERT_EQ(ts.peekChar(), '\0');
    EXPECT_TRUE(ts.prev().isEmpty());
    EXPECT_TRUE(ts.next().isEmpty());
    EXPECT_TRUE(ts.atEnd());
}

TEST_F(TypingSourceTest, FirstCharTest)
{
    ts.open(fileName);

    ASSERT_EQ(ts.peekChar(), buffer[0]);
    EXPECT_TRUE(ts.prev().isEmpty());
    EXPECT_EQ(ts.next(), buffer.first(16));
    EXPECT_FALSE(ts.atEnd());
}

TEST_F(TypingSourceTest, BeginBufferTest)
{
    ts.open(fileName, 7);

    ASSERT_EQ(ts.peekChar(), buffer[7]);
    EXPECT_EQ(ts.prev(), buffer.mid(0, 7));
    EXPECT_EQ(ts.next(), buffer.mid(7, 16));
    EXPECT_FALSE(ts.atEnd());
}

TEST_F(TypingSourceTest, MidBufferTest)
{
    ts.open(fileName, buffer.size() / 2);

    ASSERT_EQ(ts.peekChar(), buffer[buffer.size() / 2]);
    EXPECT_EQ(ts.prev(), buffer.mid(buffer.size() / 2 - 16, 16));
    EXPECT_EQ(ts.next(), buffer.mid(buffer.size() / 2, 16));
    EXPECT_FALSE(ts.atEnd());
}

TEST_F(TypingSourceTest, EndBufferTest)
{
    ts.open(fileName, buffer.size() - 7);

    ASSERT_EQ(ts.peekChar(), buffer[buffer.size() - 7]);
    EXPECT_EQ(ts.prev(), buffer.mid(buffer.size() - 7 - 16, 16));
    EXPECT_EQ(ts.next(), buffer.mid(buffer.size() - 7, 16));
    EXPECT_FALSE(ts.atEnd());
}

TEST_F(TypingSourceTest, LastCharTest)
{
    ts.open(fileName, buffer.size());

    ASSERT_EQ(ts.peekChar(), '\0');
    EXPECT_EQ(ts.prev(), buffer.last(16));
    EXPECT_TRUE(ts.next().isEmpty());
    EXPECT_TRUE(ts.atEnd());
}
