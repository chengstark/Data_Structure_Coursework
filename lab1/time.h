class Time{
public:
    Time();
    Time(int iHour, int iMinute, int iSecond);

    // Accessors
    int getHour() const;
    int getMinute() const;
    int getSecond() const;

    // Modifiers
    void setHour(int iHour);
    void setMinute(int iMinute);
    void setSecond(int iSecond);

    // Other functions
    void PrintAMPM();

private:
    int hour;
    int minute;
    int second;
};

// other functions
bool IsEarlierThan(const Time& t1, const Time& t2);