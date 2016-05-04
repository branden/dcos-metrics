#pragma once

#include <mesos/mesos.pb.h>
#include <mesos/slave/resource_estimator.hpp>
#include <process/future.hpp>
#include <stout/try.hpp>

#include "io_runner.hpp"

namespace stats {

  class ResourceEstimatorProcess;

  /**
   * Implements the mesos ResourceEstimator interface, to hook into mesos' stats on container
   * resources.
   */
  class ResourceEstimatorModule : public mesos::slave::ResourceEstimator {
   public:
    ResourceEstimatorModule(std::shared_ptr<IORunner> io_runner);
    virtual ~ResourceEstimatorModule();

    Try<Nothing> initialize(
        const lambda::function<process::Future<mesos::ResourceUsage>()>& usage);

    process::Future<mesos::Resources> oversubscribable();

   private:
    std::unique_ptr<ResourceEstimatorProcess> impl;
  };

}