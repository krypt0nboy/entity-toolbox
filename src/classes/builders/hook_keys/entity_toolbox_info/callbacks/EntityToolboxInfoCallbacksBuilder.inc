<?php

/**
 * Class CallbacksValueBuilder
 */
class EntityToolboxInfoCallbacksBuilder extends EntityToolboxInfoKeyBuilder {
  /**
   * @var array $callbacksTypesInfo
   */
  protected $callbacksTypesInfo = array();

  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'self_key'    => 'callbacks',
        'model_class' => 'EntityToolboxInfoCallbacksModel'
      ),
      $args
    );
    parent::__construct($args);
  }
}