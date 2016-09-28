using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class Palette : MonoBehaviour {
    public GridLayoutGroup grid;
    
    private int cellColCnt = 3;
    private float cellWidth;

	void Awake () {
        grid = GetComponent<GridLayoutGroup>();
	}

    void Start () {
        // 한 줄당 슬롯 개수 설정.
        grid.constraintCount = cellColCnt;

        // 슬롯 사이즈 설정.
        cellWidth = GetComponent<RectTransform>().rect.width / cellColCnt;
        grid.cellSize = new Vector2(cellWidth, cellWidth);
    }

    public void selectColor(Button button)
    {
        GameObject.Find("Canvas/Panel/Image - Select Color").transform.GetComponent<Image>().color = button.gameObject.GetComponent<Image>().color;
        GameObject.Find("UIMgr").GetComponent<UIMgr>().setSelectColor(button.gameObject.GetComponent<Image>().color);
    }

    public void selectPosition(Button button)
    {
        GameObject.Find("UIMgr").GetComponent<UIMgr>().setSelectPosition(button.name);
    }

	
	void Update () {
	}
}
