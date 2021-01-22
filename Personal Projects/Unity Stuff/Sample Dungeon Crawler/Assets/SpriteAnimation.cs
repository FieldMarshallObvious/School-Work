using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SpriteAnimation : MonoBehaviour
{
    public SpriteRenderer SpriteRenderer;
    public Sprite[] spriteArray;
    private Sprite curSprite;
    private int curIndex = 0;
    private float changeTime = 0.05f;
    private bool passed = false;
    private bool reverse = false;


    // Start is called before the first frame update
    void Start()
    {
        //SpriteRenderer = inputSpriteRender;
        //this.GetComponent<SpriteRenderer>().sprite = curSprite;
        StartCoroutine("ChangeSprite");
    }

    // Update is called once per frame
    void Update()
    {
        this.GetComponent<SpriteRenderer>().sprite = SpriteRenderer.sprite;
    }

    IEnumerator ChangeSprite( )
    {

        SpriteRenderer.sprite = spriteArray[curIndex];
        /*if (reverse == true)
            SpriteRenderer.flipX = true; 
        else
            SpriteRenderer.flipX = false;
        */
        if (passed != true)
            curIndex++;
        
        else
            curIndex--;
        if (curIndex >= spriteArray.Length - 1)
        {
            passed = true;
        }
        if (curIndex <= 0 )
        {
            passed = false;
        }

        yield return new WaitForSeconds(changeTime);
        StartCoroutine("ChangeSprite");
    }

}
