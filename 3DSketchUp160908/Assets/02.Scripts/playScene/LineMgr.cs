using UnityEngine;
using System.Collections;

public class LineMgr : MonoBehaviour {
    public Transform rotX, rotZ;
    public Transform raise;
    public Color cRed;
    public bool isRotate = false;
    public bool isRaise = false;

    private Transform cam, target;
    private float dist = 200.0f;

	void Awake () {
        cam = GameObject.Find("ARCamera").transform;
        target = transform.parent;

        // init
        if (rotX == null)
        {
            rotX = transform.FindChild("3Drotate - X");
            rotZ = transform.FindChild("3Drotate - Z");
        }

        // off
        if (rotX != null)
        {
            rotX.gameObject.SetActive(false);
            rotZ.gameObject.SetActive(false);
            raise.gameObject.SetActive(false);
        }
	}
	
	void Update () {
        // 카메라와의 거리에따라 자동으로 Line의 길이 조정.
        dist = Vector3.Distance(cam.position, target.position);

        LineRenderer lr = transform.FindChild("Line - X").GetComponent<LineRenderer>();
        lr.SetPosition(0, new Vector3(-dist/2.0f, 1, 0));
        lr.SetPosition(1, new Vector3(dist/2.0f, 1, 0));

        lr = transform.FindChild("Line - Y").GetComponent<LineRenderer>();
        lr.SetPosition(1, new Vector3(0, dist/2.0f, 0));

        lr = transform.FindChild("Line - Z").GetComponent<LineRenderer>();
        lr.SetPosition(0, new Vector3(0, 1, -dist/2.0f));
        lr.SetPosition(1, new Vector3(0, 1, dist/2.0f));

        // rotate icon position (dynamic)
        if (isRotate == true)
        {
            rotX.position = new Vector3(-dist/4.0f, 0f, 0f);
            rotZ.position = new Vector3(0f, 0f, -dist/4.0f);
        }

        if (isRaise == true)
        {
            raise.localScale = new Vector3(dist * 0.00005f, dist * 0.00005f, dist * 0.00005f);
        }
    }

    public void OnRotate ()
    {
        // On
        isRotate = true;
        rotX.gameObject.SetActive(true);
        rotZ.gameObject.SetActive(true);

        AutoSelect();
    }

    public void OnRaise()
    {
        Transform select = null;

        // On
        isRaise = true;
        raise.gameObject.SetActive(true);
        //Debug.Log("OK");

        select = AutoSelect();
        
        if (select != null)
            raise.position = new Vector3(select.position.x, select.position.y, select.position.z);
        else
        {
            raise.gameObject.SetActive(false);
            isRaise = false;
        }
    }

    public Transform AutoSelect()
    {
        // all objects
        Transform[] objs = target.FindChild("DrawObjects").GetComponentsInChildren<Transform>();
        Transform sel = null;

        // cancel "select object"
        for (int i = objs.Length - 1; i > 0; i--)
        {
            if (objs[i].GetComponent<MyObject>().isSelected == true)
            {
                // get materials from selected object
                Material[] mats = objs[i].GetComponent<MeshRenderer>().materials;
                Color[] _colors = objs[i].GetComponent<MyObject>().colors;

                // color change
                for(int j = 0; j < mats.Length; j++)
                    mats[j].color = _colors[j];
                
                objs[i].GetComponent<MyObject>().isSelected = false;
            }
        }

        // Find Last 2D object
        for (int i = objs.Length - 1; i > 0; i--)
        {
            if (objs[i].GetComponent<MyObject>().is3D == false)
            {
                // get materials from selected object
                Material[] mats = objs[i].GetComponent<MeshRenderer>().materials;

                // color change
                for(int j = 0; j < mats.Length; j++)
                    mats[j].color = cRed;
                
                objs[i].GetComponent<MyObject>().isSelected = true;
                sel = objs[i];
                break;
            }
        }

        return sel;
    }

    public void OffRotate ()
    {
        isRotate = false;

        rotX.gameObject.SetActive(false);
        rotZ.gameObject.SetActive(false);
    }

    public void OffRaise()
    {
        isRaise = false;

        raise.gameObject.SetActive(false);
    }

    public void ReSelectRaise(Transform select)
    {
        if (select != null)
            raise.position = new Vector3(select.position.x, select.position.y, select.position.z);
        else
            Debug.Log("Error) ReSelectRaise() select is Null;");
    }
}
