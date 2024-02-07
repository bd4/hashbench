#include "common.hpp"


static hpt_t hpt_key = {"node17.acmehpc", 234, 792};
static hp_t hp_key = {"node17.acmehpc", 234};


static void BM_hpt_at(benchmark::State& state) {
  std::unordered_map<hpt_t, int64_t> hpt_to_int64;
  for (auto _ : state) {
    hpt_to_int64[hpt_key] = 12;
    auto val = hpt_to_int64.at(hpt_key);
    benchmark::DoNotOptimize(val);
  }
}

static void BM_hpt_operator(benchmark::State& state) {
  std::unordered_map<hpt_t, int64_t> hpt_to_int64;
  for (auto _ : state) {
    hpt_to_int64[hpt_key] = 12;
    auto val = hpt_to_int64[hpt_key];
    benchmark::DoNotOptimize(val);
  }
}

static void BM_hp_at(benchmark::State& state) {
  std::unordered_map<hp_t, int64_t> hp_to_int64;
  for (auto _ : state) {
    hp_to_int64[hp_key] = 12;
    auto val = hp_to_int64.at(hp_key);
    benchmark::DoNotOptimize(val);
  }
}

static void BM_hp_operator(benchmark::State& state) {
  std::unordered_map<hp_t, int64_t> hp_to_int64;
  for (auto _ : state) {
    hp_to_int64[hp_key] = 12;
    auto val = hp_to_int64[hp_key];
    benchmark::DoNotOptimize(val);
  }
}



BENCHMARK(BM_hpt_at);
BENCHMARK(BM_hpt_operator);

BENCHMARK(BM_hp_at);
BENCHMARK(BM_hp_operator);


BENCHMARK_MAIN();
