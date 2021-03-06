#pragma once

#include <map>
#include <memory>
#include <string>

#include "Disruptor/TypeInfo.h"

#include "Disruptor.PerfTests/TestInfo.h"


namespace Disruptor
{
namespace PerfTests
{

    class TestRepository
    {
    public:
        static const TestRepository& instance();

        std::vector< ThroughputTestInfo > allThrougputTests() const;
        bool tryGetThroughputTest(const std::string& testName, ThroughputTestInfo& testInfo) const;

        std::vector< LatencyTestInfo > allLatencyTests() const;
        bool tryGetLatencyTest(const std::string& testName, LatencyTestInfo& testInfo) const;

    private:
        TestRepository();

        template <class TTest>
        void registerTest()
        {
            static_assert(std::is_base_of< IThroughputTest, TTest >::value || std::is_base_of< ILatencyTest, TTest >::value,
                          "TTest should implement IThroughputTest or ILatencyTest");

            registerTest(Utils::getMetaTypeInfo< TTest >(), std::make_shared< TTest >());
        }

        void registerTest(const TypeInfo& typeInfo, const std::shared_ptr< IThroughputTest >& testInstance);
        void registerTest(const TypeInfo& typeInfo, const std::shared_ptr< ILatencyTest >& testInstance);

        std::map< std::string, ThroughputTestInfo > m_throughputTestInfosByName;
        std::map< std::string, LatencyTestInfo > m_latencyTestInfosByName;
    };

} // namespace PerfTests
} // namespace Disruptor
