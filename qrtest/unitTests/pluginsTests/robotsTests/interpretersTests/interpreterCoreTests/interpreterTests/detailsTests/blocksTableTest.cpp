#include "blocksTableTest.h"

#include <QtCore/QSharedPointer>

#include "src/interpreter/details/blocksTable.h"
#include "support/dummyBlocksFactory.h"

using namespace qrTest::robotsTests::interpreterCoreTests;
using namespace qrTest::robotsTests::interpreterCoreTests::detailsTests;
using namespace interpreterCore::interpreter::details;

using namespace ::testing;

void BlocksTableTest::SetUp()
{
	QSharedPointer<DummyBlockFactory> blocksFactory(new DummyBlockFactory());

	ON_CALL(mBlocksFactoryManager, addFactory(_)).WillByDefault(Return());
	EXPECT_CALL(mBlocksFactoryManager, addFactory(_)).Times(0);

	ON_CALL(mBlocksFactoryManager, block(_)).WillByDefault(
			Invoke([=] (qReal::Id const &id) {
					return blocksFactory->block(id);
			} )
			);
	EXPECT_CALL(mBlocksFactoryManager, block(_)).Times(AtLeast(0));

	ON_CALL(mBlocksFactoryManager, providedBlocks()).WillByDefault(
			Invoke([=] { return blocksFactory->providedBlocks(); } )
			);
	EXPECT_CALL(mBlocksFactoryManager, providedBlocks()).Times(0);
}

TEST_F(BlocksTableTest, blocksCreation)
{
	BlocksTable table(mBlocksFactoryManager);
	interpreterBase::blocksBase::BlockInterface *block1 = table.block(qReal::Id("a", "b", "c", "d"));
	interpreterBase::blocksBase::BlockInterface *block2 = table.block(qReal::Id("a", "b", "c", "d"));
	interpreterBase::blocksBase::BlockInterface *block3 = table.block(qReal::Id("a", "b", "c", "e"));
	ASSERT_NE(nullptr, block1);
	ASSERT_EQ(block1, block2);
	ASSERT_NE(nullptr, block3);
	ASSERT_NE(block1, block3);
}

TEST_F(BlocksTableTest, clear)
{
	BlocksTable table(mBlocksFactoryManager);
	interpreterBase::blocksBase::BlockInterface *block1 = table.block(qReal::Id("a", "b", "c", "d"));
	interpreterBase::blocksBase::BlockInterface *block2 = table.block(qReal::Id("a", "b", "c", "d"));
	interpreterBase::blocksBase::BlockInterface *block3 = table.block(qReal::Id("a", "b", "c", "e"));
	ASSERT_NE(nullptr, block1);
	ASSERT_EQ(block1, block2);
	ASSERT_NE(nullptr, block3);
	ASSERT_NE(block1, block3);
	block1->setObjectName("block1");
	block3->setObjectName("block3");
	ASSERT_EQ(QString("block1"), block1->objectName());
	ASSERT_EQ(QString("block3"), block3->objectName());
	table.clear();
	interpreterBase::blocksBase::BlockInterface *block4 = table.block(qReal::Id("a", "b", "c", "d"));
	interpreterBase::blocksBase::BlockInterface *block5 = table.block(qReal::Id("a", "b", "c", "d"));
	interpreterBase::blocksBase::BlockInterface *block6 = table.block(qReal::Id("a", "b", "c", "e"));
	ASSERT_NE(nullptr, block4);
	ASSERT_EQ(block4, block5);
	ASSERT_NE(nullptr, block6);
	ASSERT_NE(block4, block6);
	ASSERT_NE(QString("block1"), block4->objectName());
	ASSERT_NE(QString("block1"), block5->objectName());
	ASSERT_NE(QString("block3"), block6->objectName());
}