#pragma once

#include <memory>
#include <string>
#include <vector>

#include "envoy/common/pure.h"
#include "envoy/stats/tag.h"

#include "absl/strings/string_view.h"

namespace Envoy {
namespace Stats {

class TagProducer {
public:
  virtual ~TagProducer() {}

  /**
   * Take a metric name and a vector then add proper tags into the vector and
   * return an extracted metric name. The tags array will be populated with
   * name/value pairs extracted from the full metric name, using the regular
   * expressions in source/common/config/well_known_names.cc. For example, the
   * stat name "vhost.foo.vcluster.bar.c1" would have "foo" extracted as the
   * value of tag "vhost" and "bar" extracted as the value of tag
   * "vcluster", so this will populate tags with {"vhost", "foo"} and
   * {"vcluster", "bar"}, and return "vhost.vcluster.c1".
   *
   * @param metric_name std::string a name of Stats::Metric (Counter, Gauge, Histogram).
   * @param tags std::vector a set of Stats::Tag.
   */
  virtual std::string produceTags(absl::string_view metric_name, std::vector<Tag>& tags) const PURE;
};

typedef std::unique_ptr<const TagProducer> TagProducerPtr;

} // namespace Stats
} // namespace Envoy
