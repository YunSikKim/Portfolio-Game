using UnityEngine;
using System.Collections;
using UnityEngine.SceneManagement;

public class UIMgr : MonoBehaviour
{

    public GameObject CUBE;
    public GameObject CYLINDER;
    public GameObject SPHERE;
    public GameObject TRIANGULAR;
    public GameObject CONE;
    public GameObject DOUBLECONE;

    private GameObject obj;
    private Color curColor;
    private int curPosition;

    void Start()
    {
        Debug.Log("Log : " + SceneData.data.type);
        Debug.Log("Log : " + SceneData.data.position);
        Debug.Log("Log : " + SceneData.data.scale);

        if (SceneData.data.type == "cube")
        {
            Debug.Log("Cube");
            GameObject.Find("Canvas/Panel/Panel - Planar/Cube").SetActive(true);
            obj = Instantiate(CUBE) as GameObject;
        }
        else if (SceneData.data.type == "cylinder")
        {
            Debug.Log("Cylinder");
            GameObject.Find("Canvas/Panel/Panel - Planar/Cylinder").SetActive(true);
            obj = Instantiate(CYLINDER) as GameObject;
        }
        else if (SceneData.data.type == "sphere")
        {
            Debug.Log("Sphere");
            GameObject.Find("Canvas/Panel/Panel - Planar/Sphere").SetActive(true);
            obj = Instantiate(SPHERE) as GameObject;
        }
        else if (SceneData.data.type == "triangular")
        {
            Debug.Log("Triangular");
            GameObject.Find("Canvas/Panel/Panel - Planar/Triangular").SetActive(true);
            obj = Instantiate(TRIANGULAR) as GameObject;
        }
        else if (SceneData.data.type == "cone")
        {
            Debug.Log("Cone");
            GameObject.Find("Canvas/Panel/Panel - Planar/Cone").SetActive(true);
            obj = Instantiate(CONE) as GameObject;
        }
        else if (SceneData.data.type == "doublecone")
        {
            Debug.Log("DoubleCone");
            GameObject.Find("Canvas/Panel/Panel - Planar/DoubleCone").SetActive(true);
            obj = Instantiate(DOUBLECONE) as GameObject;
        }

        obj.GetComponent<MyObject>().index = SceneData.data.index;
        obj.GetComponent<MyObject>().type = SceneData.data.type;
        obj.transform.position = SceneData.data.position;
        obj.transform.localScale = SceneData.data.scale * 300;
        obj.transform.localRotation = SceneData.data.rotate;
        obj.GetComponent<MyObject>().is3D = SceneData.data.is3D;

        obj.GetComponent<Renderer>().materials = SceneData.data.materials;

        obj.transform.parent = GameObject.Find("ImageTarget").transform;
    }

    public void setSelectColor(Color color)
    {
        curColor = color;
    }

    public void setSelectPosition(string name)
    {
        switch(SceneData.data.type)
        {
            case "cube":
                if (name == "Front")
                    curPosition = 2;
                else if (name == "Top")
                    curPosition = 4;
                else if (name == "Left")
                    curPosition = 3;
                else if (name == "Right")
                    curPosition = 0;
                else if (name == "Bottom")
                    curPosition = 5;
                else if (name == "Rear")
                    curPosition = 1;
            break;
            case "cylinder":
                if (name == "Side")
                    curPosition = 0;
                else if (name == "Top")
                    curPosition = 1;
                else if (name == "Bottom")
                    curPosition = 2;
            break;
            case "sphere":
                if (name == "Front")
                    curPosition = 0;
            break;
            case "triangular":
                if (name == "Rear")
                    curPosition = 4;
                else if (name == "Top")
                    curPosition = 1;
                else if (name == "Left")
                    curPosition = 3;
                else if (name == "Right")
                    curPosition = 2;
                else if (name == "Bottom")
                    curPosition = 0;
            break;
            case "cone":
            if (name == "Side")
                curPosition = 1;
            else if (name == "Bottom")
                curPosition = 0;
            break;
            case "doublecone":
            if (name == "Front")
                curPosition = 0;
            break;
        }

        obj.GetComponent<Renderer>().materials[curPosition].color = curColor;
    }

    public void apply()
    {
        Debug.Log(obj.GetComponent<MyObject>().index);
        Debug.Log(ObjectData.objList);

        for (int i = 0; i < ObjectData.objList.Count; i++)
        {
            if(obj.GetComponent<MyObject>().index == ObjectData.objList[i].index)
            {
                ObjectData.objList[i].materials = obj.GetComponent<Renderer>().materials;
            }
        }

        SceneManager.LoadScene("play");
    }

    public void cancel()
    {
        SceneManager.LoadScene("play");
    }
}
