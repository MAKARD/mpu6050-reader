class TimeStep {
    public: 
        TimeStep(double);
        double getCurrentStep(double);
        void tick();
    private:
        int iterator;
        double currentTime;
        double previousTime;
};
