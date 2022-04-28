namespace HitMe.Types.Device
{
    public enum MessageType
    {
        /// <summary>
        /// Parser error on device.
        /// </summary>
        PARSEERR = -1,
        
        /// <summary>
        /// Request message.
        /// </summary>
        REQUEST_MSG = 0,
        
        /// <summary>
        /// Answer message.
        /// </summary>
        ANSWER_MSG,

        /// <summary>
        /// Status message.
        /// </summary>
        STATUS_MSG
    };
}
