<?php

/**
 * Class ReferenceDependentTraits
 */
trait ReferenceDependentTraits {
  /**
   * @var string $reference
   */
  protected $reference;
  /**
   * @var array $referenceInfo
   */
  protected $referenceInfo = array();

  /**
   * @return string
   */
  public function getReference() {
    return $this->reference;
  }

  /**
   * @param string $reference
   */
  public function setReference($reference) {
    $this->reference = $reference;
  }

  /**
   * @return array
   */
  public function getReferenceInfo() {
    return $this->referenceInfo;
  }

  /**
   * @param array $referenceInfo
   */
  public function setReferenceInfo($referenceInfo) {
    $this->referenceInfo = $referenceInfo;
  }
}