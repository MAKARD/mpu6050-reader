class TimeStep {
  public:
    TimeStep();
    double getCurrentStep();
  private:
    double currentTime;
    double previousTime;
};
