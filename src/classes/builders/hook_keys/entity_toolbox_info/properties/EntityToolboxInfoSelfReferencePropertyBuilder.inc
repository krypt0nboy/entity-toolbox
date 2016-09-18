<?php

/**
 * Class EntityToolboxInfoSelfReferencePropertyBuilder
 */
class EntityToolboxInfoSelfReferencePropertyBuilder extends EntityToolboxInfoReferencePropertyBuilder {
  /** {{@inheritdoc}} */
  protected function constructSet($args) {
    parent::constructSet($args);
    $this->setRequiresRebuild(TRUE);
  }

  /** {{@inheritdoc}} */
  protected function postSetReference() {
    if ($this->getPhase() == self::PHZ__REBUILD) {
      parent::postSetReference();
    }
  }

  /** {{@inheritdoc}} */
  public function setReferenceInfo($referenceInfo) {
    parent::setReferenceInfo($referenceInfo);
    $this->setRequiresRebuild(FALSE);
  }
}