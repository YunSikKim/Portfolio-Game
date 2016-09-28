using UnityEngine;
using System.Collections;

public class Data : MonoBehaviour {
    public int index = -1;
    public string type = "";
    public Vector3 position = new Vector3(0, 0, 0);
    public Vector3 scale = new Vector3(0, 0, 0);
    public Quaternion rotate = new Quaternion();
    public Material[] materials;

    public bool is3D = false;
}
