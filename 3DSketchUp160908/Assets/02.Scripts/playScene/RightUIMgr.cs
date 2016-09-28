using UnityEngine;
using System.Collections;
using UnityEngine.SceneManagement;

public class RightUIMgr : MonoBehaviour {
    public bool isObjectDel;
    public bool stateObjectSelect;
    public GameObject obj;
    public TouchMgr touchmgr;

    void Start ()
    {
        isObjectDel = false;

        touchmgr = GameObject.Find("TouchMgr").GetComponent<TouchMgr>();

        // Paint Scene -> Play Scene
        if(ObjectData.objList.Count != 0)
        {
            // Object Load
            for (int i = 0; i < ObjectData.objList.Count; i++)
            {
                if (ObjectData.objList[i].type == "cube")
                {
                    Debug.Log("Cube");
                    obj = Instantiate(touchmgr.CUBE) as GameObject;
                }
                else if (ObjectData.objList[i].type == "cylinder")
                {
                    Debug.Log("Cylinder");
                    obj = Instantiate(touchmgr.CYLINDER) as GameObject;
                }
                else if (ObjectData.objList[i].type == "sphere")
                {
                    Debug.Log("Sphere");
                    obj = Instantiate(touchmgr.SPHERE) as GameObject;
                }
                else if (ObjectData.objList[i].type == "triangular")
                {
                    Debug.Log("Triangular");
                    obj = Instantiate(touchmgr.TRIANGULAR) as GameObject;
                }
                else if (ObjectData.objList[i].type == "cone")
                {
                    Debug.Log("Cone");
                    obj = Instantiate(touchmgr.CONE) as GameObject;
                }
                else if (ObjectData.objList[i].type == "doublecone")
                {
                    Debug.Log("DoubleCone");
                    obj = Instantiate(touchmgr.DB_CONE) as GameObject;
                }

                obj.GetComponent<MyObject>().index = ObjectData.objList[i].index;
                obj.GetComponent<MyObject>().type = ObjectData.objList[i].type;
                obj.transform.position = ObjectData.objList[i].position;
                obj.transform.localScale = ObjectData.objList[i].scale * 300;
                obj.transform.localRotation = ObjectData.objList[i].rotate;
                obj.transform.GetComponent<MyObject>().is3D = ObjectData.objList[i].is3D;
                obj.transform.GetComponent<Renderer>().materials = ObjectData.objList[i].materials;

                obj.transform.parent = GameObject.Find("ImageTarget/DrawObjects").transform;
            }
        }

        stateObjectSelect = false;
    }

    public void AllObjectDel ()
    {
        GameObject.Find("Lines").GetComponent<LineMgr>().isRotate = false;
        GameObject.Find("Lines").GetComponent<LineMgr>().isRaise = false;

        Transform[] objs = GameObject.Find("DrawObjects").GetComponentsInChildren<Transform>();
        for (int i = 1; i < objs.Length; i++)
        {
            Destroy(objs[i].gameObject);
        }
    }

    public void setObjectSelect(bool state)
    {
        stateObjectSelect = state;
    }

    public void LoadPaintScene (GameObject obj)
    {
        Debug.Log("LoadPaintScene");
        //// 넘길 데이터.
        //GameObject sel_obj = null;
        //Transform[] objs = GameObject.Find("DrawObjects").GetComponentsInChildren<Transform>();
        //for (int i = objs.Length - 1; i > 0; i--)
        //    if (objs[i].GetComponent<MyObject>().isSelected == true)
        //    {
        //        sel_obj = objs[i].gameObject;
        //    }

        SceneData.data.index = obj.GetComponent<MyObject>().index;
        SceneData.data.type = obj.GetComponent<MyObject>().type;
        SceneData.data.position = obj.transform.position;
        SceneData.data.scale = obj.transform.localScale;
        SceneData.data.rotate = obj.transform.localRotation;
        SceneData.data.materials = obj.GetComponent<Renderer>().materials;

        if (obj.GetComponent<MyObject>().is3D)
            SceneData.data.is3D = true;
        else
            SceneData.data.is3D = false;

        objectSave();

        ////SceneData.data.type = "육면체";
        ////SceneData.data.value = 3;

        //// 이동.
        SceneManager.LoadScene("paintScene");
    }

    public void setObjectDel(bool state)
    {
        isObjectDel = state;
    }

    public void objectSave()
    {
        ObjectData.objList.Clear();
        Transform[] objs = GameObject.Find("DrawObjects").GetComponentsInChildren<Transform>();
        for (int i = 1; i < objs.Length; i++)
        {
            Debug.Log(objs[i].GetComponent<MyObject>().type);
            Data data = new Data();
            data.index = objs[i].GetComponent<MyObject>().index;
            data.position = objs[i].position;
            data.rotate = objs[i].localRotation;
            data.scale = objs[i].localScale;
            data.type = objs[i].GetComponent<MyObject>().type;
            data.materials = objs[i].GetComponent<Renderer>().materials;
            data.is3D = objs[i].GetComponent<MyObject>().is3D;

            ObjectData.objList.Add(data);
        }
    }

    public void save()
    {
        Debug.Log("Save");
        objectSave();

        string str = "";
        for(int i=0; i<ObjectData.objList.Count; i++)
        {
            str += ObjectData.objList[i].type + ",";
            str += ObjectData.objList[i].index.ToString() + ",";

            str += ObjectData.objList[i].position.x.ToString() + " ";
            str += ObjectData.objList[i].position.y.ToString() + " ";
            str += ObjectData.objList[i].position.z.ToString() + ",";
            str += ObjectData.objList[i].scale.x.ToString() + " ";
            str += ObjectData.objList[i].scale.y.ToString() + " ";
            str += ObjectData.objList[i].scale.z.ToString() + ",";
            str += ObjectData.objList[i].rotate.x.ToString() + " ";
            str += ObjectData.objList[i].rotate.y.ToString() + " ";
            str += ObjectData.objList[i].rotate.z.ToString() + ",";
            if (ObjectData.objList[i].is3D)
                str += "1,";
            else
                str += "0,";
            str += ObjectData.objList[i].materials.Length + ",";

            for (int j = 0; j < ObjectData.objList[i].materials.Length; j++)
            {
                str += ObjectData.objList[i].materials[j].color.r.ToString() + " ";
                str += ObjectData.objList[i].materials[j].color.g.ToString() + " ";
                str += ObjectData.objList[i].materials[j].color.b.ToString() + ",";
            }
            str += "\n";
        }

        Debug.Log(str);

        PlayerPrefs.SetString("Data1", str);
        PlayerPrefs.SetInt("DataCnt", 1);
    }
}
