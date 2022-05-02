package com.example.stealth.models;

public class stepsModels {
    String stepsXAxis;
    int stepsYAxis;

    public stepsModels(String stepsXAxis, int stepsYAxis) {
        this.stepsXAxis = stepsXAxis;
        this.stepsYAxis = stepsYAxis;
    }

    public String getStepsXAxis() {
        return stepsXAxis;
    }

    public void setStepsXAxis(String stepsXAxis) {
        this.stepsXAxis = stepsXAxis;
    }

    public int getStepsYAxis() {
        return stepsYAxis;
    }

    public void setStepsYAxis(int stepsYAxis) {
        this.stepsYAxis = stepsYAxis;
    }

}
