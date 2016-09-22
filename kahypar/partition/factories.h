/***************************************************************************
 *  Copyright (C) 2015-2016 Sebastian Schlag <sebastian.schlag@kit.edu>
 **************************************************************************/

#pragma once

#include "meta/abstract_factory.h"
#include "meta/static_double_dispatch_factory.h"
#include "meta/static_multi_dispatch_factory.h"
#include "meta/typelist.h"
#include "partition/coarsening/i_coarsener.h"
#include "partition/initial_partitioning/i_initial_partitioner.h"
#include "partition/refinement/2way_fm_refiner.h"
#include "partition/refinement/i_refiner.h"
#include "partition/refinement/kway_fm_cut_refiner.h"
#include "partition/refinement/kway_fm_km1_refiner.h"
#include "partition/refinement/lp_refiner.h"
#include "partition/refinement/policies/2fm_rebalancing_policy.h"
#include "partition/refinement/policies/fm_stop_policy.h"

using meta::Factory;
using meta::PolicyRegistry;
using meta::StaticDoubleDispatchFactory;
using meta::StaticMultiDispatchFactory;
using meta::Typelist;

namespace partition {
using CoarsenerFactory = Factory<CoarseningAlgorithm,
                                 ICoarsener* (*)(Hypergraph&, const Configuration&,
                                                 const HypernodeWeight)>;


using RefinerFactory = Factory<RefinementAlgorithm,
                               IRefiner* (*)(Hypergraph&, const Configuration&)>;

using InitialPartitioningFactory = Factory<InitialPartitionerAlgorithm,
                                           IInitialPartitioner* (*)(Hypergraph&, Configuration&)>;

using TwoWayFMFactoryDispatcher = StaticMultiDispatchFactory<TwoWayFMRefiner,
                                                             IRefiner,
                                                             Typelist<StoppingPolicyClasses,
                                                                      RebalancingPolicyClasses> >;

using KWayFMFactoryDispatcher = StaticMultiDispatchFactory<KWayFMRefiner,
                                                           IRefiner,
                                                           Typelist<StoppingPolicyClasses> >;

using KWayKMinusOneFactoryDispatcher = StaticMultiDispatchFactory<KWayKMinusOneRefiner,
                                                                  IRefiner,
                                                                  Typelist<StoppingPolicyClasses> >;
}  // namespace partition
