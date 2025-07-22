std::mt19937_64 rng(std::chrono::system_clock::now().time_since_epoch().count());
int rand(int l, int r) {
    return uniform_int_distribution<int>(l, r)(rng);
}
