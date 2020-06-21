using UnityEngine;

public class PlayerMovement : MonoBehaviour
{

    public float speed;

    // Start is called before the first frame update
    void Start()
    {

    }

    // Update is called once per frame
    void FixedUpdate()
    {
        //Checks if the speed limit is reached

            if (Input.GetKey(KeyCode.UpArrow))
            {
                //Move the Rigidbody forwards constantly at speed you define (the blue arrow axis in Scene view)
                transform.Translate(transform.forward * speed * Time.deltaTime);
            }

            if (Input.GetKey(KeyCode.DownArrow))
            {
                //Move the Rigidbody backwards constantly at the speed you define (the blue arrow axis in Scene view)
                transform.Translate(-transform.forward * speed * Time.deltaTime);
            }

            if (Input.GetKey(KeyCode.RightArrow))
            {
                transform.Translate(transform.right * speed * Time.deltaTime);
            }

            if (Input.GetKey(KeyCode.LeftArrow))
            {
                transform.Translate(-transform.right * speed * Time.deltaTime);
            }
        
    }
}
