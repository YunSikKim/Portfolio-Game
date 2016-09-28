using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class MyObject : MonoBehaviour {
    public int index = -1;
    public bool isSelected = false;     // 만들어진 도형이 선택툴에 의해 선택되었는지. <<TouchMgr.cs>>
    public bool is3D = false;           // 입체도형인지.
    public string type = "";
    public Color[] colors;

    void Start ()
    {
        // colors backup
        Material[] mats = GetComponent<MeshRenderer>().materials;
        colors = new Color[mats.Length];

        for (int i = 0; i < mats.Length; i++)
            colors[i] = mats[i].color;
    }
}
