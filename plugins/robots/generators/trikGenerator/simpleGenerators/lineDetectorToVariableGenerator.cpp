#include "lineDetectorToVariableGenerator.h"

#include <generatorBase/generatorCustomizer.h>

using namespace trik::simple;
using namespace generatorBase::simple;

LineDetectorToVariableGenerator::LineDetectorToVariableGenerator(qrRepo::RepoApi const &repo
		, generatorBase::GeneratorCustomizer &customizer
		, qReal::Id const &id
		, QObject *parent)
	: BindingGenerator(repo, customizer, id
			, "lineDetectorToVariable.t"
			, {Binding::createDirect("@@VAR@@", "Variable")}
			, parent)
{
}
