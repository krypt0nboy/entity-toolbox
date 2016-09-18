<?php

/**
 * Class EntityPropertyInfoReferenceNumericPropertyBuilder
 */
class EntityPropertyInfoReferenceMultipleNumericPropertyBuilder extends EntityPropertyInfoReferenceNumericPropertyBuilder {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'model_class' => 'EntityPropertyInfoReferenceMultipleNumericPropertyModel',
      ),
      $args
    );
    parent::__construct($args);
  }

  /**
   *
   */
  protected function postSetReference() {
    $this->__set('reference_info', entity_get_info($this->reference));
  }
}