<?php

/**
 * Class HookInfoBuilder
 */
class HookInfoBuilder extends HookBuilder {
  use ModuleDependentTraits;

  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(array(
      'hook' => 'hook_info',
    ), $args);
    parent::__construct($args);
  }

  /** {{@inheritdoc}} */
  public function build() {
    $this->buildEntityGroupHooks();
    $this->buildEntityHooks();
    $this->unsetKeysEval();

    return $this->build;
  }

  /**
   * Builds the module's entity group hooks.
   * @param null|string $entityGroup
   *
   * @return array
   */
  public function buildEntityGroupHooks($entityGroup = NULL) {
  }

  /**
   * Builds the module's entities hooks.
   * @param null|string $entityType
   *
   * @return array
   */
  public function buildEntityHooks($entityType = NULL) {
  }
}