using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class Load : MonoBehaviour
{
    public TouchMgr touchmgr;

    private GameObject objectCreate;

    public string type = "";
    public int index = -1;
    public Vector3 position = new Vector3(0, 0, 0);
    public Vector3 scale = new Vector3(0, 0, 0);
    public Quaternion rotate = Quaternion.identity;
    public bool is3D = false;
    public int matCount = -1;
    public Material[] materials;
    public int curMat = 0;

    public static bool loaded = false;

    // Use this for initialization
    void Awake()
    {
        if (!loaded)
            DataLoad();
    }

    public void DataLoad()
    {
        Debug.Log("Load");

        // clear
        Transform[] trs = GameObject.Find("ImageTarget/DrawObjects").GetComponentsInChildren<Transform>();
        for (int x = 1; x < trs.Length; x++)
            Destroy(trs[x].gameObject);

        // Load
        int count = PlayerPrefs.GetInt("DataCnt");
        for (int i = 0; i < count; i++)
        {
            string str = PlayerPrefs.GetString("Data" + (i + 1));
            string[] obj = str.Split('\n');

            for (int j = 0; j < obj.Length - 1; j++)
            {
                Debug.Log("Object" + (i + 1));
                curMat = 0;

                string[] attr = obj[j].Split(',');

                for (int k = 0; k < attr.Length - 1; k++)
                {
                    string[] value = attr[k].Split(' ');


                    switch (k)
                    {
                        case 0:
                            Debug.Log(value[0]);

                            type = value[0];
                            break;
                        case 1:
                            Debug.Log(value[0]);

                            index = int.Parse(value[0]);
                            break;
                        case 2:
                            Debug.Log(value[0]);
                            Debug.Log(value[1]);
                            Debug.Log(value[2]);

                            position.x = float.Parse(value[0]);
                            position.y = float.Parse(value[1]);
                            position.z = float.Parse(value[2]);
                            break;
                        case 3:
                            Debug.Log(value[0]);
                            Debug.Log(value[1]);
                            Debug.Log(value[2]);

                            scale.x = float.Parse(value[0]);
                            scale.y = float.Parse(value[1]);
                            scale.z = float.Parse(value[2]);
                            break;
                        case 4:
                            Debug.Log(value[0]);
                            Debug.Log(value[1]);
                            Debug.Log(value[2]);

                            rotate.x = float.Parse(value[0]);
                            rotate.y = float.Parse(value[1]);
                            rotate.z = float.Parse(value[2]);
                            break;
                        case 5:
                            Debug.Log(value[0]);

                            if (int.Parse(value[0]) == 0)
                                is3D = false;
                            else
                                is3D = true;
                            break;
                        case 6:
                            Debug.Log(value[0]);

                            matCount = int.Parse(value[0]);

                            materials = new Material[matCount];
                            break;
                        default:
                            Debug.Log(value[0]);
                            Debug.Log(value[1]);
                            Debug.Log(value[2]);

                            Color color;
                            float r, g, b;
                            float.TryParse(value[0], out r);
                            float.TryParse(value[1], out g);
                            float.TryParse(value[2], out b);

                            color.r = r;
                            color.g = g;
                            color.b = b;
                            color.a = 1.0f;

                            Debug.Log("CurMat = " + curMat);

                            Material material = new Material(Shader.Find("Diffuse"));
                            material.color = color;

                            materials[curMat] = material;
                            curMat++;
                            break;
                    }
                }

                if (type == "cube")
                {
                    Debug.Log("Cube");
                    objectCreate = Instantiate(touchmgr.CUBE) as GameObject;
                }
                else if (type == "rect")
                {
                    Debug.Log("rect");
                    objectCreate = Instantiate(touchmgr.CUBE) as GameObject;
                }
                else if (type == "cylinder")
                {
                    Debug.Log("Cylinder");
                    objectCreate = Instantiate(touchmgr.CYLINDER) as GameObject;
                }
                else if (type == "sphere")
                {
                    Debug.Log("Sphere");
                    objectCreate = Instantiate(touchmgr.SPHERE) as GameObject;
                }
                else if (type == "triangular")
                {
                    Debug.Log("Triangular");
                    objectCreate = Instantiate(touchmgr.TRIANGULAR) as GameObject;
                }
                else if (type == "cone")
                {
                    Debug.Log("Cone");
                    objectCreate = Instantiate(touchmgr.CONE) as GameObject;
                }
                else if (type == "doublecone")
                {
                    Debug.Log("DoubleCone");
                    objectCreate = Instantiate(touchmgr.DB_CONE) as GameObject;
                }

                objectCreate.GetComponent<MyObject>().index = index;
                objectCreate.GetComponent<MyObject>().type = type;
                objectCreate.transform.position = position;
                objectCreate.transform.localScale = scale * 300;
                objectCreate.transform.localRotation = rotate;
                objectCreate.transform.GetComponent<MyObject>().is3D = is3D;
                objectCreate.transform.GetComponent<Renderer>().materials = materials;

                objectCreate.transform.parent = GameObject.Find("ImageTarget/DrawObjects").transform;
            }
        }

        loaded = true;
    }

    private Text tabTitle;
    public void ClickSave()
    {
        tabTitle = GameObject.Find("Text - TabTitle").GetComponent<Text>();
        tabTitle.text = "저장";
    }
    public void ClickLoad()
    {
        tabTitle = GameObject.Find("Text - TabTitle").GetComponent<Text>();
        tabTitle.text = "열기";
    }
}

