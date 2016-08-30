<?php

/**
 * Class ContribHookBuilderFactory
 */
class ContribHookBuilderFactory extends HookBuilderFactory {
  /**
   * @var array $toolboxInfo
   */
  protected $toolboxInfo;

  /** {{@inheritdoc}} */
  public function __construct($name, $entityType) {
    $this->toolboxInfo = entity_toolbox_get_info($entityType);
    $args              = array(
      'hook'      => $name,
      'fieldable' => $this->toolboxInfo['fieldable'] ? 'Fieldable' : 'NotFieldable',
    );
    parent::__construct($name, $entityType, $args);
  }
}