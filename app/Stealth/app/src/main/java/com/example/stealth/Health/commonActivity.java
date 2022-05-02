package com.example.stealth.Health;

import androidx.appcompat.app.AppCompatActivity;

import android.graphics.Color;
import android.os.Bundle;

import com.example.stealth.databinding.ActivityCommonBinding;
import com.github.mikephil.charting.data.BarData;
import com.github.mikephil.charting.data.BarDataSet;
import com.github.mikephil.charting.data.BarEntry;
import com.github.mikephil.charting.data.CombinedData;
import com.github.mikephil.charting.data.Entry;
import com.github.mikephil.charting.data.LineData;
import com.github.mikephil.charting.data.LineDataSet;
import com.github.mikephil.charting.utils.ColorTemplate;

import java.util.ArrayList;

public class commonActivity extends AppCompatActivity {
    ActivityCommonBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        binding = ActivityCommonBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());
        LineDataSet lineEntries = new LineDataSet(lineChartData(),"tests");
        LineData linearData = new LineData(lineEntries);
        BarDataSet barEntries = new BarDataSet(BarChartData(),"tests");
        barEntries.setColors(ColorTemplate.MATERIAL_COLORS);
        barEntries.setValueTextColor(Color.RED);
        barEntries.setValueTextSize(16f);
        BarData barData = new BarData(barEntries);
        CombinedData data=new CombinedData();
        data.setData(linearData);
        data.setData(barData);
        binding.barChart.setData(data);



    }
    private ArrayList<BarEntry> BarChartData(){
        ArrayList<BarEntry> bar =new ArrayList<>();
        bar.add(new BarEntry(2014,1000));
        bar.add(new BarEntry(2015,900));
        bar.add(new BarEntry(2016,100));
        bar.add(new BarEntry(2017,600));
        bar.add(new BarEntry(2018,800));
        return bar;

    }
    private ArrayList<Entry> lineChartData(){
        ArrayList<Entry> line =new ArrayList<>();
        line.add(new Entry(2014,1000));
        line.add(new Entry(2015,900));
        line.add(new Entry(2016,100));
        line.add(new Entry(2017,600));
        line.add(new Entry(2018,800));
        return line;

    }


}