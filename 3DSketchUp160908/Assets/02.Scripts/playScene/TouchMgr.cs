using UnityEngine;
using System.Collections;

public class TouchMgr : MonoBehaviour {
    public Camera ARcam;

    // Mouse
    public bool onDrag = false;
    public bool onRaise = false;
    public Vector3 startPos, mousePos;
    private Vector3 gabPos;

    // dist
    Transform cam, target;
    float dist = 500.0f;

    // create object
    private GameObject OBJECT;      // 만들 Prefab
    private GameObject myObj;       // 현재 만들고있는 도형.
    public bool isReady = false;    // 도형을 만들 타이밍인지.
    private float minScale = 0.01f;
    public static int idx = 0;

    // 충돌체크.
    private Ray ray;
    private RaycastHit hit;
    public Color cRed;
    public bool isHit = false;     // 충돌체크한 도형이 존재하는지.
    private bool isMoveXY = true;

    // make 3D
    public GameObject CUBE;
    public GameObject CYLINDER;     // 원기둥.
    public GameObject SPHERE;       // 구.
    public GameObject TRIANGULAR;
    public GameObject CONE, DB_CONE;    // 원뿔.
    private LineMgr lineMgr;

	void Awake ()
    {
        cam = GameObject.Find("ARCamera").transform;
        target = GameObject.Find("ImageTarget").transform;
        lineMgr = target.FindChild("Lines").GetComponent<LineMgr>();
	}
	
	void Update ()
    {
        dist = Vector3.Distance(cam.position, target.position);
        ray = Camera.main.ScreenPointToRay(Input.mousePosition);
        #if UNITY_EDITOR
        Debug.DrawRay(ray.origin, ray.direction * 500.0f, Color.cyan);
        #endif


        if (Input.GetMouseButtonDown(0))
        {
            // 생성 준비중인 object가 있으면...
            if (isReady == true && OBJECT != null)
            {
                // mouse attribute
                float rotVal = cam.rotation.y >= 0.0f? cam.rotation.y*180.0f : -cam.rotation.y*180.0f;
                if (60.0f > rotVal || rotVal >= 160.0f)
                {   // x, y
                    startPos = Camera.main.ScreenToWorldPoint(new Vector3(Input.mousePosition.x, Input.mousePosition.y, -Camera.main.transform.position.z));
                    isMoveXY = true;
                }
                else
                {   // y, z
                    startPos = Camera.main.ScreenToWorldPoint(new Vector3(Input.mousePosition.x, Input.mousePosition.y, -Camera.main.transform.position.x));
                    isMoveXY = false;
                }
                onDrag = true;

                // create object
                myObj = Instantiate(OBJECT) as GameObject;
                myObj.GetComponent<MyObject>().index = idx++;
                myObj.transform.parent = GameObject.Find("DrawObjects").transform;
                myObj.transform.position = new Vector3(0f, startPos.y, 0f);
                myObj.transform.localScale = new Vector3(minScale, myObj.transform.localScale.y, minScale);
                if (OBJECT.name == "Cube")
                    myObj.GetComponent<MyObject>().type = "rect";
                else if (OBJECT.name == "Cylinder")
                    myObj.GetComponent<MyObject>().type = "circle";
                else if (OBJECT.name == "Triangular")
                    myObj.GetComponent<MyObject>().type = "triangle";
                else
                    myObj.GetComponent<MyObject>().type = OBJECT.name;

                myObj.SetActive(true);
            }

            // 도형 충돌체크.
            else if (Physics.Raycast(ray, out hit, dist, 1 << 8))
            {
                // 도형 선택 후 페인트씬으로 넘어감
                if (GameObject.Find("RightUIMgr").GetComponent<RightUIMgr>().stateObjectSelect == true)
                {
                    Debug.Log(hit);
                    GameObject.Find("RightUIMgr").GetComponent<RightUIMgr>().LoadPaintScene(hit.transform.gameObject);
                }
                // 도형 개별 삭제.
                else if (GameObject.Find("RightUIMgr").GetComponent<RightUIMgr>().isObjectDel == true)
                {
                    Destroy(hit.transform.gameObject);
                    GameObject.Find("RightUIMgr").GetComponent<RightUIMgr>().isObjectDel = false;
                }
                // 3D화 모드중일때 도형 선택.
                else if (lineMgr.isRotate == true || lineMgr.isRaise == true)
                {
                    Transform[] objs = GameObject.Find("DrawObjects").GetComponentsInChildren<Transform>();
                    // cancel "select object"
                    for (int i = objs.Length - 1; i > 0; i--)
                    {
                        if (objs[i].GetComponent<MyObject>().isSelected == true)
                        {
                            SelectMyObject(false, objs[i]);
                            objs[i].GetComponent<MyObject>().isSelected = false;
                            break;
                        }
                    }
                    // 충돌된 object select
                    hit.transform.GetComponent<MyObject>().isSelected = true;
                    SelectMyObject(true, hit.transform);    // coloring

                    // Raise 화살표 이동.
                    if(lineMgr.isRaise == true)
                        lineMgr.ReSelectRaise(hit.transform);
                }
                // 일반 상황.
                else
                {
                    // Move Object
                    hit.transform.GetComponent<MyObject>().isSelected = true;
                    SelectMyObject(true, hit.transform);

                    // 어느 방향인지 계산.
                    mousePos = Camera.main.ScreenToWorldPoint(new Vector3(Input.mousePosition.x, Input.mousePosition.y, FindBack()));
					gabPos = hit.transform.position - mousePos;
                    onDrag = true;
                    isHit = true;
                }
            }

            // 3D Rotate 충돌체크.
            else if (Physics.Raycast(ray, out hit, dist, 1 << 9))
            {
                // find select object
                GameObject sel_obj = null;
                Transform[] objs = GameObject.Find("DrawObjects").GetComponentsInChildren<Transform>();
                for (int i = objs.Length - 1; i > 0; i--)
                    if (objs[i].GetComponent<MyObject>().isSelected == true)
                        sel_obj = objs[i].gameObject;

                if (sel_obj != null)
                {
                    // 2D 도형 삭제.
                    Transform beforeTr = sel_obj.transform;
                    Destroy(sel_obj);

                    // 3D 도형 생성. rect
                    if (sel_obj.GetComponent<MyObject>().type == "rect")
                    {
                        // 실린더 생성.
                        GameObject _obj = Instantiate(CYLINDER) as GameObject;
                        _obj.transform.parent = GameObject.Find("DrawObjects").transform;
                        _obj.transform.position = beforeTr.position;

                        switch (hit.transform.name)
                        {
                            case "3Drotate - X":
                                Debug.Log("3Drotate - X");
                                // rect -> 뚜껑이 왼오른쪽에 달린 실린더.
                                _obj.transform.Rotate(0f, 0f, 90f);
                                _obj.transform.localScale = new Vector3(beforeTr.localScale.z, beforeTr.localScale.x, beforeTr.localScale.z) * 0.9f;
                                break;
                            case "3Drotate - Z":
                                Debug.Log("3Drotate - Z");
                                // rect -> 뚜껑이 앞뒤쪽에 달린 실린더.
                                _obj.transform.Rotate(-90f, 0f, 0f);
                                _obj.transform.localScale = new Vector3(beforeTr.localScale.x, beforeTr.localScale.z, beforeTr.localScale.x) * 0.9f;
                                break;
                            default:
                                break;
                        }
                        // 실린더 마무리.
                        _obj.GetComponent<MyObject>().is3D = true;
                        _obj.GetComponent<MyObject>().type = "cylinder";
                        _obj.GetComponent<MyObject>().index = beforeTr.GetComponent<MyObject>().index;
                        _obj.SetActive(true);
                    }

                    // circle -> 구.
                    else if (sel_obj.GetComponent<MyObject>().type == "circle")
                    {
                        // 구 생성.
                        GameObject _obj = Instantiate(SPHERE) as GameObject;
                        _obj.transform.parent = GameObject.Find("DrawObjects").transform;
                        _obj.transform.position = beforeTr.position;
                        _obj.transform.localScale = new Vector3(beforeTr.localScale.x, beforeTr.localScale.x, beforeTr.localScale.x) * 1.2f;
                        _obj.GetComponent<MyObject>().is3D = true;
                        _obj.GetComponent<MyObject>().type = "sphere";
                        _obj.GetComponent<MyObject>().index = beforeTr.GetComponent<MyObject>().index;
                    }

                    // triangle
                    else if (sel_obj.GetComponent<MyObject>().type == "triangle")
                    {
                        GameObject _obj;
                        switch (hit.transform.name)
                        {
                            case "3Drotate - X":
                                Debug.Log("3Drotate - X");
                                // 원뿔.
                                _obj = Instantiate(CONE) as GameObject;
                                _obj.transform.parent = GameObject.Find("DrawObjects").transform;
                                _obj.transform.position = beforeTr.position;
                                _obj.transform.localScale = new Vector3(beforeTr.localScale.x, beforeTr.localScale.x, beforeTr.localScale.z);
                                _obj.GetComponent<MyObject>().is3D = true;
                                _obj.GetComponent<MyObject>().type = "cone";
                                _obj.GetComponent<MyObject>().index = beforeTr.GetComponent<MyObject>().index;
                                break;
                            case "3Drotate - Z":
                                Debug.Log("3Drotate - Z");
                                // 팽이모양.
                                _obj = Instantiate(DB_CONE) as GameObject;
                                _obj.transform.parent = GameObject.Find("DrawObjects").transform;
                                _obj.transform.position = beforeTr.position;
                                _obj.transform.localScale = new Vector3(beforeTr.localScale.x, beforeTr.localScale.x, beforeTr.localScale.z);
                                _obj.GetComponent<MyObject>().is3D = true;
                                _obj.GetComponent<MyObject>().type = "doublecone";
                                _obj.GetComponent<MyObject>().index = beforeTr.GetComponent<MyObject>().index;
                                break;
                            default:
                                break;
                        }
                    }

                    // 회전 종료.
                    lineMgr.OffRotate();
                }
            }

            // 3D Raise 충돌체크.
            else if (Physics.Raycast(ray, out hit, dist, 1 << 10))
            {
                startPos = Camera.main.ScreenToWorldPoint(new Vector3(Input.mousePosition.x, Input.mousePosition.y, -Camera.main.transform.position.z));
                onDrag = true;
                onRaise = true;
                Debug.Log("Raise OK");
            }
        }
        else if (Input.GetMouseButtonUp(0))
        {
            onDrag = false;

            // off move
            if (isHit == true)
            {
                hit.transform.GetComponent<MyObject>().isSelected = false;
                SelectMyObject(false, hit.transform);
                isHit = false;
            }
            else if (onRaise == true)
            {
                Transform[] objs = GameObject.Find("DrawObjects").GetComponentsInChildren<Transform>();

                // cancel "select object"
                for (int i = objs.Length - 1; i > 0; i--)
                {
                    if (objs[i].GetComponent<MyObject>().isSelected == true)
                    {
                        SelectMyObject(false, objs[i]);
                        objs[i].GetComponent<MyObject>().isSelected = false;
                        break;
                    }
                }

                lineMgr.OffRaise();
                onRaise = false;
                Debug.Log("Raise END");
            }
        }
        else if (onDrag)
        {
            // Move Selected Object ... 
            if (isHit == true /*&& hit.transform.GetComponent<MyObject>().isSelected == true*/)
            {
                mousePos = Camera.main.ScreenToWorldPoint(new Vector3(Input.mousePosition.x, Input.mousePosition.y, FindBack()));

                if (isMoveXY)   // x, y축 이동.
                    hit.transform.position = new Vector3(mousePos.x + gabPos.x, mousePos.y + gabPos.y, hit.transform.position.z);
                else    // y, z축 이동.
                    hit.transform.position = new Vector3(hit.transform.position.x, mousePos.y + gabPos.y, mousePos.z + gabPos.z);

                return;
            }

            // Raise Selected Object ...
            else if (lineMgr.isRaise == true)
            {
                // find select object
                GameObject sel_obj = null;
                Transform[] objs = GameObject.Find("DrawObjects").GetComponentsInChildren<Transform>();
                for (int i = objs.Length - 1; i > 0; i--)
                    if (objs[i].GetComponent<MyObject>().isSelected == true)
                        sel_obj = objs[i].gameObject;

                mousePos = Camera.main.ScreenToWorldPoint(new Vector3(Input.mousePosition.x, Input.mousePosition.y, -Camera.main.transform.position.z));
                float _size = Mathf.Abs(mousePos.y - startPos.y) / 150.0f;       // 100.0f???
                sel_obj.transform.localScale = new Vector3(sel_obj.transform.localScale.x, _size / 2, sel_obj.transform.localScale.z);
                lineMgr.raise.transform.position = new Vector3(lineMgr.raise.transform.position.x, mousePos.y/2.0f + sel_obj.transform.position.y/2.0f, lineMgr.raise.transform.position.z);

                sel_obj.GetComponent<MyObject>().is3D = true;
                if(sel_obj.GetComponent<MyObject>().type == "rect")
                    sel_obj.GetComponent<MyObject>().type = "cube";
                if (sel_obj.GetComponent<MyObject>().type == "circle")
                    sel_obj.GetComponent<MyObject>().type = "cylinder";
                if (sel_obj.GetComponent<MyObject>().type == "triangle")
                    sel_obj.GetComponent<MyObject>().type = "triangular";

                return;
            }

            // Creating Object ...
            mousePos = Camera.main.ScreenToWorldPoint(new Vector3(Input.mousePosition.x, Input.mousePosition.y, FindBack()));
//            if (isMoveXY)
//            {   // x, y
//                mousePos = Camera.main.ScreenToWorldPoint(new Vector3(Input.mousePosition.x, Input.mousePosition.y, -Camera.main.transform.position.z));
//            }
//            else
//            {   // y, z
//                mousePos = Camera.main.ScreenToWorldPoint(new Vector3(Input.mousePosition.x, Input.mousePosition.y, -Camera.main.transform.position.x));
//            }

            float size = Mathf.Abs(mousePos.x - startPos.x) / 100.0f;       // 100.0f???
            myObj.transform.localScale = new Vector3(size, myObj.transform.localScale.y, size);

            isReady = false;
        }

	} // update


    public void SetMyObj (GameObject obj)
    {
        OBJECT = obj;
        isReady = true;
    }

    private void SelectMyObject (bool onOff, Transform tr)
    {
        // select
        if (onOff == true)
        {
            // get materials from selected object
            Material[] mats = tr.GetComponent<MeshRenderer>().materials;

            // color change
            for (int i = 0; i < mats.Length; i++)
                mats[i].color = cRed;
        }
        // cancle select
        else
        {
            // get materials from selected object
            Material[] mats = tr.GetComponent<MeshRenderer>().materials;
            Color[] _colors = tr.GetComponent<MyObject>().colors;

            // color change
            for (int i = 0; i < mats.Length; i++)
                mats[i].color = _colors[i];
        }
    }

    private float FindBack ()
    {
        isMoveXY = false;
        float rotY = cam.rotation.y * 180.0f;

        // front
        if (-65.0f <= rotY && rotY <= 65.0f)
        {
            isMoveXY = true;
            return -Camera.main.transform.position.z;
        }
        else if (-150.0f <= rotY && rotY <= -65.0f)
        {
            // left
            if (cam.rotation.x < 0) // 음수. -160.0f <= rotY && rotY <= -110
                return -Camera.main.transform.position.x;
            // right
            else
                return Camera.main.transform.position.x;
        }
        // left
        else if (65.0f < rotY && rotY <= 130.0f)
        {
            return -Camera.main.transform.position.x;
        }
        // defalt; back
        else  //if (rotY <= -150.0f)
        {
            isMoveXY = true;
            return Camera.main.transform.position.z;
        }
    }
}
